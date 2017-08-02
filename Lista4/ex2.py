# Constant
POINT_O = (0, 0)


# This Function calculates the GCD of A and B by the euclides extend algorithm, such that ax + by = gcd(a, b)
# Return an integer corresponding to GCD of A and B
def extend_euclids_function(a, b):
    x0, x1, y0, y1 = 1, 0, 0, 1
    while b != 0:
        q, a, b = a // b, b, a % b
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1

    return x0


# Function that make sum operation in Elliptic Curve Cryptography
# This sum is defined by some rules in ECC
# Return a point in format (X,Y)
def sum_in_ecc(pointP, pointQ, a, p):
    Xp, Yp = pointP
    Xq, Yq = pointQ

    if pointP == POINT_O:  # O is the additive identity O = -O, P+O=P
        result_point = pointQ
    elif pointQ == POINT_O:  # O is the additive identity O = -O, Q+O=Q
        result_point = pointP
    elif Xp == Xq and (Yp == (-Yq) % p):  # P-Q = O, the negative of a point is -P = (x,-y)
        result_point = POINT_O
    else:
        delta = 0
        if pointP != pointQ:  # Distinct Points,P != -Q
            dividend = (Yq-Yp) % p
            divider = (Xq-Xp) % p
            delta = (dividend*extend_euclids_function(divider, p)) % p
        elif pointP == pointQ:  # Equal points, add point to itself
            dividend = (3*(Xp**2)+a) % p
            divider = (2*Yp) % p
            delta = (dividend*extend_euclids_function(divider, p)) % p

        Xr = ((delta**2) - Xp - Xq) % p
        Yr = (delta*(Xp-Xr) - Yp) % p
        result_point = (Xr, Yr)

    return result_point


# This function verify if A,B and P values satisfy equation: 4a^3 + 27b^2 ( mod p ) != 0
# If values satisfy the equation return 0, if not return 1
def verify_if_equation_is_satisfied(a, b, p):
    # print("[INFO]Verificando se valores inseridos satisfazem a equação")
    # print("[DEBUG]A= ", a, "B= ", b, "P= ", p)
    aux1 = 4*(a**3) % p
    aux2 = 27*(b**2) % p
    aux3 = (aux1 + aux2) % p

    if(aux3 != 0):
        # print("[INFO]Valores validos!")
        # Valid values
        return 0
    else:
        # print("[INFO]Valores invalidos!")
        # Invalid Values
        return 1


# The order of a point corresponds corresponds to the number of sums needed to get the point in infinit O
# The return is a integer corresponding to order of the point
def find_point_order(point, a, p):
    order = 1
    x, y = point
    while point != POINT_O:
        point = sum_in_ecc(point, (x, y), a, p)
        order += 1
    return order


# Return a list with all points of the elliptic curve equation generate by the numbers a,b and p.
# Example of return format ( (X1,Y1),(X2,Y2),(X3,Y3),(X4,Y4),...,(Xn,Yn) )
def find_all_points_in_equation(a, b, p):
    # print("[INFO]Na função para descobrir os pontos!")
    points_coordinate = []
    x_point = 0  # Value of coordinate in X axies

    while x_point < p:
    	# For each value of x there are 0, 1, or 2 possible values of y:
        y2 = (((x_point**3) % p) + ((a*x_point) % p) + b) % p  # Value of y^2 in the analised point
        y_point = 0
        while y_point < p:  # Interate in each value of y less than p
            if((y_point**2) % p == y2):
                if y_point != (-y_point) % p:  # Add the atual point and "his inverse" 
                    points_coordinate.append((x_point, y_point))
                    points_coordinate.append((x_point, (-y_point) % p))
                else:
                    points_coordinate.append((x_point, y_point))
                break; # Point find, pass to next y value
                
            y_point += 1  # Interate one value in Y axis
           
        x_point += 1  # Interate one value in X axis
        
    return points_coordinate


if __name__ == "__main__":

    a = int(input("Insira o valor A: "))
    b = int(input("Insira o valor B: "))
    p = int(input("Insira o valor P: "))

    while verify_if_equation_is_satisfied(a, b, p) == 1:
        print("Valores Inválidos!!\n")
        a = int(input("Insira o valor A: "))
        b = int(input("Insira o valor B: "))
        p = int(input("Insira o valor P: "))

    points = find_all_points_in_equation(a, b, p)
    orders = [find_point_order(point, a, p) for point in points]

    i = 0
    for order in orders:
        print("Ponto:", points[i], "  Ordem: ", order)
        i += 1

    # Make a list of order values and the points,than order than from smallest to the highest point Order
    order_points_values = [value for value in list(zip(orders, points))]
    order_points_values.sort()

    print("Ponto de maior ordem (Ordem,(Xp,Yp)): ", format(order_points_values[-1]))
    print("Quantidade de pontos: %d" % (len(points)))
