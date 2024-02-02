import pandas as pd

time_dataset = {'TimeStamp': ['2021-09-01 09:00:00', '2021-09-01 10:00:00', '2021-09-01 11:00:00']};

time_df = pd.DataFrame(time_dataset)

print("Original DataFrame\n")
print(time_df)

hour_df = pd.to_datetime(time_df['TimeStamp']).dt.hour
print("\n\nHour DataFrame\n")
print(hour_df)