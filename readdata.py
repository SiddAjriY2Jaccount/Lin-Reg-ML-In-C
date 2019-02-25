import pandas as pd
fields = ["Close"]
#df = pd.read_csv('data.csv')
#saved_column = df.Close
#print(saved_column)
#print(df['Close'].loc[1:], df['Shares Traded'], df['Turnover (Rs. Cr)'])
df = pd.read_csv('datacpse.csv')
list1 = list(df['Close'])
print(list1)

list2 = [2061.15, 2038.95, 2004.1, 2031.65, 2039.75, 2038.65, 2024.15, 2018.35, 2025.3, 2013.55, 2030.5, 2033.9, 2031.5, 2028.2, 2006.0, 1996.25, 1981.45, 1977.1, 1965.55, 1967.7, 1966.2, 1963.9, 1977.3, 1981.8, 1970.1, 1937.6, 1968.8, 1987.05, 1932.55, 1910.8, 1925.85, 1886.2, 1861.7, 1896.8, 1895.25, 1901.1, 1944.1, 1954.95, 1996.3, 1998.9]
print(list2)

print(min(list2))

print(max(list2))

sum = 0
j=0
for i in range(40):
    sum += i
    j += 1
    print(i, sum)
mean = sum/j
print(j, mean)
