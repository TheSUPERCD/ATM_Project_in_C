import sys
def decrypt(messege,private_key,n):
    lm=len(messege)
    encdata=['']*lm
    for i in range(0,lm):
        encdata[i]=chr((ord(messege[i])**private_key)%n)
    return encdata
filename=str(sys.argv[1])
f_security=open(filename,"r",encoding='utf-8')
if f_security.mode=='r':
    encSecurityCode=f_security.read()
else:
    print("error in reading file\n")
f_security.close()
private_key=109
n=2117
de_encSecurityCode=decrypt(encSecurityCode,private_key,n)
f_security=open(filename,"w",encoding='utf-8')
for i in range(0,len(de_encSecurityCode)):
    f_security.write(de_encSecurityCode[i])
f_security.close()