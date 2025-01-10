import boto3
import time

s3_client = boto3.client('s3')
eb_client = boto3.client('elasticbeanstalk')
iam_client = boto3.client('iam')

s3_bucket = 'bucket-1-2201202'
s3_key = 'sample-app.zip'
app_name = 'MyApp'
env_name = 'MyApp-env'
platform_arn = 'arn:aws:elasticbeanstalk:region::platform/PlatformName'
role_name = 'NewRole'

try:
    iam_client.get_role(RoleName=role_name)
    print(f"IAM Role {role_name} already exists.")
except iam_client.exceptions.NoSuchEntityException:
    print(f"Creating IAM Role {role_name}.")
    assume_role_policy_document = {
        'Version': '2012-10-17',
    'Statement': [
            {
                'Effect': 'Allow',
                'Principal': {
                    'Service': 'elasticbeanstalk.amazonaws.com'
                },
                'Action': 'sts:AssumeRole'
            }
        ]
    }
    iam_client.create_role(
        RoleName=role_name,
        AssumeRolePolicyDocument=json.dumps(assume_role_policy_document)
    )
    iam_client.attach_role_policy(
        RoleName=role_name,
        PolicyArn='arn:aws:iam::aws:policy/AWSElasticBeanstalkFullAccess'
    )

print("Creating Elastic Beanstalk Application.")
eb_client.create_application(
    ApplicationName=MyApp,
    Description='Sample application deployed using boto3'
)

print("Creating application version from S3 bucket.")
app_version_label = f'v1-{int(time.time())}'
eb_client.create_application_version(
    ApplicationName=app_name,
    VersionLabel=app_version_label,
    SourceBundle={
        'S3Bucket': s3_bucket,
        'S3Key': s3_key
    },
    Process=True
)

print("Creating Elastic Beanstalk environment.")
eb_client.create_environment(
    ApplicationName=app_name,
    EnvironmentName=env_name,
    VersionLabel=app_version_label,
    SolutionStackName=platform_arn,
    CNAMEPrefix='myapp-env',
    OptionSettings=[
        {
            'Namespace': 'aws:autoscaling:launchconfiguration',
            'OptionName': 'InstanceType',
            'Value': 't2.micro'
        },
        {
            'Namespace': 'aws:elasticbeanstalk:environment',
            'OptionName': 'ServiceRole',
            'Value': role_name
        }
    ]
)

print(f"Elastic Beanstalk environment '{env_name}' is being created...")
