import sys
def encrypt(messege,public_key,n):
    lm=len(messege)
    encdata=['']*lm
    for i in range(0,lm):
        encdata[i]=chr((ord(messege[i])**public_key)%n)
    return encdata
filename=str(sys.argv[1])
f_security=open(filename,"r",encoding='utf-8')
if f_security.mode=='r':
    securityCode=f_security.read()
else:
    print("error in reading file\n")
f_security.close()
public_key=37
n=2117
encSecurityCode=encrypt(securityCode,public_key,n)
f_security=open(filename,"w",encoding='utf-8')
for i in range(0,len(encSecurityCode)):
    f_security.write(encSecurityCode[i])
f_security.close()