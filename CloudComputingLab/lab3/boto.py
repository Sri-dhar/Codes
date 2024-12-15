import boto3
import base64
import time

ec2 = boto3.client('ec2')

ami_id = 'ami-0522ab6e1ddcc7055'  
instance_type = 't2.micro'
key_name = 'keypair-lab3-new'  
security_group_name = 'MySecurityGroup'
description = 'Security group for allowing HTTP traffic on port 80'

existing_groups = ec2.describe_security_groups(GroupNames=[security_group_name])
if existing_groups['SecurityGroups']:
    security_group_id = existing_groups['SecurityGroups'][0]['GroupId']
    print(f'Using existing security group with ID: {security_group_id}')
else:
    response = ec2.create_security_group(GroupName=security_group_name, Description=description)
    security_group_id = response['GroupId']
    print(f'Created security group with ID: {security_group_id}')

    ec2.authorize_security_group_ingress(
        GroupId=security_group_id,
        IpPermissions=[
            {
                'IpProtocol': 'tcp',
                'FromPort': 80,
                'ToPort': 80,
                'IpRanges': [{'CidrIp': '0.0.0.0/0'}] 
            }
        ]
    )
    print(f'Added rule to allow inbound traffic on port 80 to security group: {security_group_name}')

with open('startup.sh', 'r') as file:
    user_data_script = file.read()

user_data_encoded = base64.b64encode(user_data_script.encode('utf-8')).decode('utf-8')

response = ec2.run_instances(
    ImageId=ami_id,
    InstanceType=instance_type,
    KeyName=key_name,
    MinCount=1,
    MaxCount=1,
    UserData=user_data_encoded,
    SecurityGroupIds=[security_group_id]  
)

instance_id = response['Instances'][0]['InstanceId']
print(f'Launched EC2 instance with ID: {instance_id}')

print('Waiting for the instance to be running...')
ec2.get_waiter('instance_running').wait(InstanceIds=[instance_id])
instance_description = ec2.describe_instances(InstanceIds=[instance_id])
instance_public_ip = instance_description['Reservations'][0]['Instances'][0].get('PublicIpAddress')
print(f'Instance Public IP: {instance_public_ip}')

