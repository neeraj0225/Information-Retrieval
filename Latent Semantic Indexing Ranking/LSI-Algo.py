import numpy as np
import pandas as pd
import math
from sklearn.feature_extraction.text import CountVectorizer

doc1 = 'Shipment of gold damaged in an fire'
doc2 = 'Delivery of silver arrived in an silver truck'
doc3 = 'Shipment of gold arrived in an truck'
query = 'gold silver truck'

docs = ['Shipment of gold damaged in an fire','Delivery of silver arrived in an silver truck','Shipment of gold arrived in an truck','gold silver truck']

vec = CountVectorizer()
X = vec.fit_transform(docs)
df = pd.DataFrame(X.toarray(), columns=vec.get_feature_names())
print('Note : The last row is of query ')
print('\n')
print(df)

TermMatrix = pd.DataFrame(df).to_numpy()
ro = len(TermMatrix)
col = len(TermMatrix[0])
q = TermMatrix[ro-1]
print('The query vector is : ')
print(q)
print("\n")
TermMatrix = np.delete(TermMatrix,ro-1,0)
TermMatrix = np.transpose(TermMatrix)
print('The Term Document Matrix is : ')
print(TermMatrix)
print("\n")

U, S, V = np.linalg.svd(TermMatrix)
print(U)
print("\n")
print(S)
print("\n")
print(V)
print("\n")

rank = np.linalg.matrix_rank(TermMatrix)
k = 2
U = U[:,:k]
print(U)

V = V[:,:k]
print(V)

Supdated = np.zeros((k,k))
for i in range(0,k):
    Supdated[i][i] = S[i];
print(Supdated)

Sinv = np.linalg.inv(Supdated)
print(Sinv)

q = np.transpose(q)
print(q)

newQuery = np.dot(q,np.dot(U,Sinv))
print(newQuery)

r,c = np.shape(TermMatrix)
rankDoc = np.zeros(c)
for i in range(0,c):
    dotProd = 0
    sumSquares1 = 0
    sumSquares2 = 0
    Total = 0
    for j in range(0,k):
        dotProd = newQuery[j]*V[i][j] + dotProd
        sumSquares1 = sumSquares1 + V[i][j]*V[i][j]
        sumSquares2 = sumSquares2 + newQuery[j]*newQuery[j]
        Total = math.sqrt(sumSquares1)*math.sqrt(sumSquares2)
    rankDoc[i] = dotProd/Total

print(rankDoc)

DocRank = np.argsort(rankDoc) 
DocRank = np.flip(DocRank)
for j in range(0,c):
    print(DocRank[j]+1)
