%170191
%Ayush Gupta

% clearing the entire workspace and window for testing
clear all;
clc;

% Declaring the equation given in the format required
A = [0 1 1; 1 4 2; -2 -8 3];
b = [1; -2; 32];
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
            disp(A)
            disp(pivot_row)
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

% Printing the final result
disp("Soluting for x:")
disp(x);