from ex2 import *


# Function that make multiply operation in Elliptic Curve Cryptography
# In ECC multiply consist in sum operation
def multiply_in_ecc(k, point, a, p):
    result = POINT_O
    pointAux = point

    for bit in range(k.bit_length()):
        if (k >> bit) & 1:
            result = sum_in_ecc(result, pointAux, a, p)
        pointAux = sum_in_ecc(pointAux, pointAux, a, p)  # Double point value.
    return result


# Function that make the encryption operation in Elliptic Curve Cryptography
# C1 = k*PointG
# C2 = PointP + k*PublicKey
# Return two points in format: ( (X,Y) , (X,Y) ) that are C1,C2
def encryption(pointG, pointP, public_key, a, p):
    k = int(input("Insira um valor inteiro aleatorio: "))

    point_C1 = multiply_in_ecc(k, pointG, a, p)
    point_C2 = sum_in_ecc(pointP,
                          multiply_in_ecc(k, public_key, a, p),
                          a,
                          p)
    return (point_C1, point_C2)


# Function that make the decryption operation in Elliptic Curve Cryptography
# Calculates: C2 - PrivateKey*C1
# Return a point in format (X,Y)
def decryption(pointsCrip, private_key, a, p):
    aux = multiply_in_ecc(private_key, pointsCrip[0], a, p)
    decipher_point = sum_in_ecc(pointsCrip[1],
                                (aux[0],
                                (-aux[1]) % p),
                                a,
                                p)
    return decipher_point


# Return a point in format (X,Y)
def scan_point():
    point = eval(input("\tInsira o ponto no formato (x,y): "))

    return point


# Return two points in format: ( (X,Y) , (X,Y) )
def scan_two_points():
    pointC1 = eval(input("Insira o ponto C1 no formato (x,y): "))
    pointC2 = eval(input("Insira o ponto C2 no formato (x,y): "))

    return (pointC1, pointC2)

if __name__ == '__main__':
    a = int(input("Insira o valor A: "))
    b = int(input("Insira o valor B: "))
    p = int(input("Insira o valor P: "))

    while verify_if_equation_is_satisfied(a, b, p) == 1:
        print("Valores Inválidos!!\n")
        a = int(input("Insira o valor A: "))
        b = int(input("Insira o valor B: "))
        p = int(input("Insira o valor P: "))

    print("PONTO BASE G: ")
    pointG = scan_point()

    print("PONTO A SER CIFRADO P: ")
    pointP = scan_point()

    opcao = 0
    while opcao != 3:
        print("======= MENU =======")
        print("1- Criptografa")
        print("2- Descriptografa")
        print("3- Finalizar")
        opcao = int(input("Opcao: "))

        if (opcao == 1):

            print("Insira a chave publica do destinatario para cifracao")
            public_key = scan_point()
            pointsCrip = encryption(pointG, pointP, public_key, a, p)
            print("Pontos C1 e C2: ", pointsCrip)

        elif opcao == 2:
            pointsCrip = scan_two_points()
            private_key = int(input("Insira a chave privada para decifrar: "))
            pointP = decryption(pointsCrip, private_key, a, p)
            print("Ponto decifrado P': ", pointP)
