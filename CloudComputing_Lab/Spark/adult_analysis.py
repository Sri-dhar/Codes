import pandas as pd
from pyspark.sql import SparkSession
from pyspark.sql.functions import col
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.clustering import KMeans
from sklearn.preprocessing import LabelEncoder

spark = SparkSession.builder \
    .appName("AdultDatasetClustering") \
    .getOrCreate()

columns = ["age", "workclass", "fnlwgt", "education", "education_num", "marital_status", 
           "occupation", "relationship", "race", "sex", "capital_gain", "capital_loss", 
           "hours_per_week", "native_country", "income"]

df = pd.read_csv("adult.data", names=columns, na_values="?")

label_encoders = {}
categorical_columns = ["workclass", "education", "native_country", "occupation", "marital_status", "sex"]
for col_name in categorical_columns:
    le = LabelEncoder()
    df[col_name] = le.fit_transform(df[col_name].fillna("Unknown"))
    label_encoders[col_name] = le

spark_df = spark.createDataFrame(df)

features = ["age", "workclass", "education"]
assembler = VectorAssembler(inputCols=features, outputCol="features")
cluster_df = assembler.transform(spark_df)

kmeans = KMeans(k=3, seed=1)
model = kmeans.fit(cluster_df)
predictions = model.transform(cluster_df)
print("\n\nClustering Results:\n\n")
predictions.select("age", "workclass", "education", "prediction").show(20       )

usa_encoded = label_encoders['native_country'].transform([' United-States'])[0]

highest_country = (spark_df.filter(col("native_country") != usa_encoded)
                   .groupBy("native_country")
                   .count()
                   .orderBy(col("count").desc())
                   .first())            

if highest_country:
    highest_country_name = label_encoders['native_country'].inverse_transform([highest_country['native_country']])[0]
    print(f"\n\nThe country with the highest number of adults except USA: {highest_country_name}\n\n")

masters_encoded = label_encoders['education'].transform([' Masters'])[0]
doctorate_encoded = label_encoders['education'].transform([' Doctorate'])[0]
tech_support_encoded = label_encoders['occupation'].transform([' Tech-support'])[0]

masters_techsupport = (spark_df.filter(
    ((col("education") == masters_encoded) | (col("education") == doctorate_encoded)) & 
    (col("occupation") == tech_support_encoded)
).count())
print(f"\n\nNumber of people who are at least Masters and work in Tech-support: {masters_techsupport}\n\n")

local_gov_encoded = label_encoders['workclass'].transform([' Local-gov'])[0]
male_encoded = label_encoders['sex'].transform([' Male'])[0]
    
married_statuses = [
    ' Married-civ-spouse',
    ' Married-spouse-absent',
    ' Married-AF-spouse'
]
married_encoded = [label_encoders['marital_status'].transform([status])[0] for status in married_statuses]

unmarried_male_localgov = (spark_df.filter(
    (~col("marital_status").isin(married_encoded)) &
    (col("sex") == male_encoded) &
    (col("workclass") == local_gov_encoded)
).count())
print(f"\n\nNumber of unmarried males working in Local-gov: {unmarried_male_localgov}\n\n")


wait = input("Press Enter to continue.")    
spark.stop()        