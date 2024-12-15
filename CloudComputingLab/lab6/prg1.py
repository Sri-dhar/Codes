import boto3

ACCESS_KEY = ""
SECRET_KEY = ""
REGION = "ap-south-1"
INSTANCE_TYPE = "db.t3.micro"
ID = "my-feedback-db"
USERNAME = "temp_1234089"
PASSWORD = "temp"
DB_PORT = 3306
DB_SIZE = 20
DB_ENGINE = "mysql"         
DB_NAME = "feedbackDB" 

client = boto3.client(
    'rds',
    region_name=REGION,
    aws_access_key_id=ACCESS_KEY,
    aws_secret_access_key=SECRET_KEY
)

def check_rds_instance_exists(db_identifier):
    try:
        response = client.describe_db_instances(DBInstanceIdentifier=db_identifier)
        if response['DBInstances']:
            return True
    except client.exceptions.DBInstanceNotFoundFault:
        return False
    except Exception as e:
        print(f"Error checking RDS instance: {e}")
        return None

def create_rds_instance():
    if check_rds_instance_exists(ID):
        print(f"RDS instance '{ID}' already exists. Skipping creation.")
    else:
        try:
            db_instance = client.create_db_instance(
                DBInstanceIdentifier=ID,
                AllocatedStorage=DB_SIZE,
                DBInstanceClass=INSTANCE_TYPE,
                Engine=DB_ENGINE,
                MasterUsername=USERNAME,
                MasterUserPassword=PASSWORD,
                Port=DB_PORT,
                DBName=DB_NAME,
                PubliclyAccessible=True,
                BackupRetentionPeriod=7,
                StorageType="gp2",
                Tags=[
                    {
                        'Key': 'Name',
                        'Value': 'MyRDSInstance'
                    }
                ]
            )
            print(f"RDS instance creation initiated: {db_instance}")
        except Exception as e:
            print(f"Error creating RDS instance: {e}")

create_rds_instance()
