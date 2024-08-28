import boto3
import time

def launch_ec2_instance(startup_script):


    ec2 = boto3.client('ec2')

    security_group = ec2.create_security_group(
        GroupName='my-security-group1',
        Description='Security group for my EC2 instance'
    )

    security_group_id = security_group['GroupId']

    ec2.authorize_security_group_ingress(
        GroupId=security_group_id,
        IpProtocol='tcp',
        FromPort=22,
        ToPort=22,
        CidrIp='0.0.0.0/0'
    )

    ec2.authorize_security_group_ingress(
        GroupId=security_group_id,
        IpProtocol='tcp',
        FromPort=80,
        ToPort=80,
        CidrIp='0.0.0.0/0'
    )

    instance = ec2.run_instances(
        ImageId='ami-0522ab6e1ddcc7055',  # Replace with your desired AMI ID
        InstanceType='t2.micro',
        MinCount=1,
        MaxCount=1,
        KeyName='keypair-lab3-new',  # Replace with your key pair name
        SecurityGroupIds=[security_group_id],
        UserData=startup_script
    )

    instance_id = instance['Instances'][0]['InstanceId']

    waiter = ec2.get_waiter('instance_running')
    waiter.wait(InstanceIds=[instance_id])

    instance = ec2.describe_instances(InstanceIds=[instance_id])['Reservations'][0]['Instances'][0]

    public_dns = instance['PublicDnsName']

    print(f"Instance launched with ID: {instance_id}")
    print(f"Public DNS: {public_dns}")

    return public_dns

if __name__ == "__main__":
    startup_script = """
    #!/bin/bash

    sudo apt-get update
    sudo apt-get install apache2 -y
    sudo apt update
    sudo apt install unzip
    curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
    unzip awscliv2.zip
    sudo ./aws/install
    aws --version
    aws configure
    aws s3 cp s3://bucket-1-2201202/index.html ~/
    aws s3 cp s3://bucket-1-2201202/error.html ~/
    aws s3 cp s3://bucket-1-2201202/script.js ~/
    aws s3 cp s3://bucket-1-2201202/styles.css ~/
    sudo systemctl start apache2                        

    """

public_dns = launch_ec2_instance(startup_script)