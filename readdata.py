import pandas as pd
fields = ["Close"]
#df = pd.read_csv('data.csv')
#saved_column = df.Close
#print(saved_column)
#print(df['Close'].loc[1:], df['Shares Traded'], df['Turnover (Rs. Cr)'])
df = pd.read_csv('data1.csv')
list1 = list(df['Turnover (Rs. Cr)'])
print(list1)
