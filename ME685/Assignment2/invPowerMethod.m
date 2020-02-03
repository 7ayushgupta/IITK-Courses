% clearing the entire workspace and window for testing
clear all;
clc;

A = [-4 14 0; -5 13 0; -1 0 2];
I = [1 0 0; 0 1 0; 0 0 1];
x0 = [1 1 1]';

x = x0;
sigma = rayleigh(A*x, x0);
fprintf("Sigma: %s \n", sigma);
A = A-sigma*I;

max_iters = 100;
curr_iters = 0;
eigenvalue = 1/sigma + sigma;
fprintf("Iteration: %d, Eigenvalue: %f, Eigenvector: (%s) \n", curr_iters, eigenvalue, sprintf('%d ', x));

while(curr_iters<max_iters)
    y = gaussian_elimination(A, x);
    c = rayleigh(x,y);
    eigenvalue = 1/c + sigma;
    x = y/norm(y);
    curr_iters=curr_iters+1;
    fprintf("Iteration: %d, Eigenvalue: %f, Eigenvector: (%s) \n", curr_iters, eigenvalue, sprintf('%d ', x/norm(x)));
end

function sigma = rayleigh(x,y)
    sigma = (dot(x, y))/dot(x,x);
end

function x = gaussian_elimination(A, b)
    n = 3;
    %Used pivot_row to store the various rows which are swapped in the pivoting
    %step for future use

    pivot_row = linspace(1,n,n);
    for k = 1 : 1 : n

        % NOTE: We are not swapping the entire row, but just storing the order
        % in which swapping is being done, to reduce complexity of program (in
        % contrast to pseudocode submitted)

        % Finding the row corresponding to max value in the given column
        max_val = abs(A(pivot_row(k), pivot_row(k)));    
        max_pos = k;    
        for l = k : 1 : n                                 
            if abs(A(pivot_row(l), pivot_row(k))) > max_val            
                max_val = abs(A(pivot_row(l), pivot_row(k)));            
                max_pos = l;            
            end
        end

        % Code for swapping the k and max_pos elements of pivot_row
        temp = pivot_row(k);
        pivot_row(k) = pivot_row(max_pos);
        pivot_row(max_pos) = temp;

        % Now changing the values of the A matrix, according to Gaussian
        % Elimination
        for i = 1 : 1 : n
            if i ~= k

                % Forward elimination
                ratio = A(pivot_row(i), k) / A(pivot_row(k), k);
                for j = k : 1 : n
                    A(pivot_row(i), j) = A(pivot_row(i), j) - A(pivot_row(k), j) * ratio;
                end

                % Back substitution
                b(pivot_row(i)) = b(pivot_row(i)) - b(pivot_row(k)) * ratio;
            end
        end
    end

    % Printing the code in the order required - which we stored in the
    % pivot_row array
    for i = 1 : 1 : n
        x(i) = b(pivot_row(i)) / A(pivot_row(i), i);
    end
end




