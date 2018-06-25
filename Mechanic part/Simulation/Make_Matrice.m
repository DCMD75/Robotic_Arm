function y = Make_Matrice(thi,ai,li,di)
y = [[cos(thi) -sin(thi)*cos(ai) sin(thi)*sin(ai) li*cos(thi)]
    [sin(thi) cos(thi)*cos(ai) -cos(thi)*sin(ai) li*sin(thi)]
    [0 sin(ai) cos(ai) di]
    [0 0 0 1]];
end