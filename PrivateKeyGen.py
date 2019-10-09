def privateKey(publicKey,p,q,n):
    for i in range(1,(p-1)*(q-1)):
        if((publicKey*i)%((p-1)*(q-1))==1):
            return i
        else:
            continue
    return -1

print("Enter the public key: \n")
publicKey=int(input())
print("Enter the number n: \n")
n=int(input())
print("Enter the prime factors p and q: \n")
p=int(input())
q=int(input())
print("The private key for the given data is: ",privateKey(publicKey,p,q,n),"\n")
                