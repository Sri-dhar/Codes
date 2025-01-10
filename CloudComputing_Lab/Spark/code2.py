import pandas as pd
from pyspark.sql import SparkSession
from pyspark.sql.functions import col
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.clustering import KMeans
from sklearn.preprocessing import LabelEncoder

# Initialize Spark session
spark = SparkSession.builder \
    .appName("AdultDatasetClustering") \
    .config("spark.hadoop.security.authentication", "simple") \
    .config("spark.executorEnv.HADOOP_USER_NAME", "YOUR_USERNAME") \
    .getOrCreate()

# Define columns
columns = ["age", "workclass", "fnlwgt", "education", "education_num", "marital_status", 
           "occupation", "relationship", "race", "sex", "capital_gain", "capital_loss", 
           "hours_per_week", "native_country", "income"]

# Load data into Pandas DataFrame for initial preprocessing
df = pd.read_csv("adult.data", names=columns, na_values="?")

# Encode categorical features using LabelEncoder
label_encoders = {}
for col_name in ["workclass", "education", "native_country", "occupation"]:
    le = LabelEncoder()
    df[col_name] = le.fit_transform(df[col_name].fillna("Unknown"))
    label_encoders[col_name] = le

# Convert Pandas DataFrame to Spark DataFrame
spark_df = spark.createDataFrame(df)

# Select features for clustering
features = ["age", "workclass", "education"]
assembler = VectorAssembler(inputCols=features, outputCol="features")
cluster_df = assembler.transform(spark_df)

# Apply KMeans clustering
kmeans = KMeans(k=3, seed=1)
model = kmeans.fit(cluster_df)
predictions = model.transform(cluster_df)
predictions.select("age", "workclass", "education", "prediction").show()

# # i) Find the country with the highest number of adults except USA
# # Get the encoded value for 'USA' using LabelEncoder if needed
usa_label = ' United-States'
try:
    usa_encoded = label_encoders['native_country'].transform([usa_label])[0]
except ValueError:
    # Display available values to help diagnose the issue
    print(f"\n\nWarning: '{usa_label}' not found. Available values are: {label_encoders['native_country'].classes_}\n\n")
    # You may want to decide on a fallback or return early if the label is essential
    usa_encoded = None
                
# if usa_encoded is not None:
#     highest_country = (spark_df.filter(col("native_country") != usa_encoded)
#                        .groupBy("native_country")
#                        .count()
#                        .orderBy(col("count").desc())
#                        .first())            

#     if highest_country:
#         highest_country_name = label_encoders['native_country'].inverse_transform([highest_country['native_country']])[0]
#         print(f"\n\nThe country with the highest number of adults except USA: {highest_country_name}\n\n")
#     else:
#         print("\n\nNo country found with the highest number of adults except USA.\n\n")
# else:
#     print("\n\nSkipping highest country calculation due to missing USA label.\n\n")

# # ii) Count of people who are at least Masters and work in "Tech-support"
# # Get encoded value for 'Masters' and 'Tech-support' if needed
# if 'Masters' in label_encoders['education'].classes_:
#     masters_encoded = label_encoders['education'].transform(['Masters'])[0]
# else:
#     print("Warning: 'Masters' not found in the education column. Available values:", label_encoders['education'].classes_)
#     masters_encoded = None

# if 'Tech-support' in label_encoders['occupation'].classes_:
#     tech_support_encoded = label_encoders['occupation'].transform(['Tech-support'])[0]
# else:
#     print("Warning: 'Tech-support' not found in the occupation column. Available values:", label_encoders['occupation'].classes_)
#     tech_support_encoded = None

# if masters_encoded is not None and tech_support_encoded is not None:
#     masters_techsupport = (spark_df.filter((col("education") == masters_encoded) & 
#                                            (col("occupation") == tech_support_encoded)).count())
#     print(f"Number of people who are at least Masters and work in Tech-support: {masters_techsupport}")
# else:
#     print("Skipping the count of people with Masters and Tech-support due to missing encoding.")

# # iii) Count of unmarried males working in "Local-gov"
# # Get encoded values for 'Local-gov' and 'Male' if needed
# local_gov_encoded = label_encoders['workclass'].transform(['Local-gov'])[0]
# male_encoded = label_encoders['sex'].transform(['Male'])[0]

# unmarried_male_localgov = (spark_df.filter((col("marital_status") != "Married-civ-spouse") &
#                                            (col("sex") == male_encoded) &
#                                            (col("workclass") == local_gov_encoded))
#                            .count())
# print(f"Number of unmarried males working in Local-gov: {unmarried_male_localgov}")


# ... (previous code remains the same until the queries section)

# i) Country with highest adults except USA (remains the same)
if usa_encoded is not None:
    highest_country = (spark_df.filter(col("native_country") != usa_encoded)
                       .groupBy("native_country")
                       .count()
                       .orderBy(col("count").desc())
                       .first())            

    if highest_country:
        highest_country_name = label_encoders['native_country'].inverse_transform([highest_country['native_country']])[0]
        print(f"\n\nThe country with the highest number of adults except USA: {highest_country_name}\n\n")

# ii) Count of people who are at least Masters and work in Tech-support
# Get encoded values for education levels and Tech-support
masters_encoded = label_encoders['education'].transform(['Masters'])[0]
doctorate_encoded = label_encoders['education'].transform(['Doctorate'])[0]
tech_support_encoded = label_encoders['occupation'].transform(['Tech-support'])[0]

masters_techsupport = (spark_df.filter(
    ((col("education") == masters_encoded) | (col("education") == doctorate_encoded)) & 
    (col("occupation") == tech_support_encoded)
).count())
print(f"Number of people who are at least Masters and work in Tech-support: {masters_techsupport}")

# iii) Count of unmarried males working in Local-gov
local_gov_encoded = label_encoders['workclass'].transform(['Local-gov'])[0]
male_encoded = label_encoders['sex'].transform(['Male'])[0]

# Define all possible marriage statuses
married_statuses = [
    'Married-civ-spouse',
    'Married-spouse-absent',
    'Married-AF-spouse'
]

unmarried_male_localgov = (spark_df.filter(
    (~col("marital_status").isin(married_statuses)) &
    (col("sex") == male_encoded) &
    (col("workclass") == local_gov_encoded)
).count())
print(f"Number of unmarried males working in Local-gov: {unmarried_male_localgov}")