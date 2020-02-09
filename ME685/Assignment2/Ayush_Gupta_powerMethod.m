%Ayush Gupta
%170191

% clearing the entire workspace and window for testing
clear all;
clc;

%declaring the workspace variables as given
A = [-4 14 0; -5 13 0; -1 0 2];
x0 = [1 1 1]';
x = x0;
max_iters = 10;
curr_iters = 0;

prev_norm = norm(x, inf);
eigenvalue = prev_norm;
fprintf("Iteration: %f, x: (%s), Eigenvalue: %f, Eigenvector: (%s) \n", curr_iters, sprintf('%d ',x), eigenvalue, sprintf('%d ', x));

%Iterations for power method
while(curr_iters<max_iters)
    x=A*x;
    %normalising vector using L-infinity norm
    new_norm = norm(x, inf);
    eigenvalue=new_norm/prev_norm;
    prev_norm = new_norm;
    curr_iters=curr_iters+1;
    fprintf("Iteration: %f, Eigenvalue: %f, Eigenvector: (%s) \n", curr_iters,eigenvalue, sprintf('%d ', x/norm(x, inf)));
end