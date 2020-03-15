%Ayush Gupta
%170191

% clearing the entire workspace and window for testing
clear all;
clc;

% Declaring the data inputs from table
W = [0.017, 0.087, 0.174, 1.11, 1.74, 4.09, 5.45, 5.96, 0.025, 0.111, 0.211, 0.999, 3.02, 4.28, 4.58, 4.68, 0.020, 0.085, 0.171, 1.29, 3.04, 4.29, 5.30, 0.020, 0.119, 0.210, 1.32, 3.34, 5.48, 0.025, 0.233, 0.783, 1.35, 1.69, 2.75, 4.83, 5.33];
R = [0.154, 0.296, 0.363, 0.531, 2.23, 3.58, 3.52, 2.40, 0.23, 0.357, 0.366, 0.771, 2.01, 3.28, 2.96, 5.10, 0.181, 0.260, 0.334, 0.87, 3.59, 3.40, 3.88, 0.180, 0.299, 0.428, 1.15, 2.83, 4.15, 0.234, 0.537, 1.47, 2.48, 1.44, 1.84, 4.66, 6.94];

% Converting to logarithmic space
x = log(W);
y = log(R);
n = length(x);

% Finding the values required in the calculation
sigma_x = sum(x);
sigma_x2 = sum(x.*x);
sigma_x3 = sum(x.*x.*x);
sigma_x4 = sum(x.*x.*x.*x);
sigma_y = sum(y);
sigma_xy = sum(x.*y);
sigma_x2y = sum(x.*x.*y);

A = [n sigma_x sigma_x2;
     sigma_x sigma_x2 sigma_x3;
     sigma_x2 sigma_x3 sigma_x4;];
b = [sigma_y, sigma_xy, sigma_x2y]';
 
%Final answer
coefficients = gaussian_elimination(A, b);
coefficients

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
