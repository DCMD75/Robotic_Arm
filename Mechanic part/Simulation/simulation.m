% example 
% détermination des coordonnée
% détermination de le Jacobien
% détermination des efforts en statique

%variables
syms th1 th2 th3 l1 l2 l3 l4 d1 d5

%matrices
A01 = Make_Matrice(0, 0, l1, d1);
A12 = Make_Matrice(th1, 0, l2, 0);
A23 = Make_Matrice(th2, 0, l3, 0);
A34 = Make_Matrice(th3, pi, l4, 0);
A45 = Make_Matrice(0, 0, 0, d5);

%Matrice de changement de base
A05 = A01*A12*A23*A34*A45;

% Coordonnée dans le repère
X = A05(1,4);
Y = A05(2,4);
Z = A05(3,4);
TH = th1+th2+th3;

% Matrice Jacobien
J = [[diff(X,d1) diff(X,th1) diff(X,th2) diff(X,th3) diff(X,d5)]
    [diff(Y,d1) diff(Y,th1) diff(Y,th2) diff(Y,th3) diff(Y,d5)]
    [diff(Z,d1) diff(Z,th1) diff(Z,th2) diff(Z,th3) diff(Z,d5)]
    [diff(TH,d1) diff(TH,th1) diff(TH,th2) diff(TH,th3) diff(TH,d5)]]

% Numériquement
% angles
th1 = 0;
th2 = 0;
th3 = 0;
% distances
d1 = 10;
d5 = -5;

% forces
F = [0;0;-10;0];

% Expression numérique approchée
round(vpa(subs(transpose(J)*F),2));
