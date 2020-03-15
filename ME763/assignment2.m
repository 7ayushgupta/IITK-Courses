% Clearing the workspace initially
clc;
clear all;

% Robot Description is given here
l1= 1;
l2 = 1;
fprintf("Created a new robot, with base at: (0,0), l1=%f m, l2=%f m\n", l1, l2);

x_init = 0;
y_constant = 0;
x_final = 2;
num_via_points = 8;

% Initialising the via-points
via_points = linspace(x_init, x_final, num_via_points);

% Initialising a graph figure
figure
hold on;
axis([-3 3 -3 3])
title('2 DOF Planar Manipulator with SVD at various points')
xlabel("x-direction")
ylabel("y-direction")
annotation('textbox',[.9 .5 .1 .2],'String','Red: Ellipse from SVD, Blue: Manipulator Links','EdgeColor','none')

% Iterating this for all points
for i = 1:1:num_via_points
    x = via_points(i);
    y = y_constant;
    [theta1, theta2] = inverse_kinematics(x, y, l1, l2);
    [x1,x2,y1,y2] = forward_kinematics(theta1, theta2, l1, l2);
    jacobian = jacobian_calculate(theta1, theta2, l1, l2);
    [U, S, V] = svd(jacobian);
    plot_ellipse(x, y, U, S);
    plot_lines(x1, x2, y1, y2);
end

% This function performs inverse kinematics
function [theta1, theta2] = inverse_kinematics(x, y, l1, l2)

    theta2 = -acos((x^2 + y^2 - l1^2 - l2^2)/(2*l1*l2));
    theta1 = atan2(y,x) + atan2(-(l2*sin(theta2)),(l1 + l2*cos(theta2)));
    
    fprintf("Inverse kinematics performed.. Theta1: %f, Theta2: %f\n", theta1, theta2);
end

% This function performs forward kinematics
function [x1, x2, y1, y2] = forward_kinematics(theta1, theta2, l1, l2)

    x1 = l1*cos(theta1);
    y1 = l1*sin(theta1);

    x2 = l1*cos(theta1) + l2*cos(theta1 + theta2);
    y2 = l1*sin(theta1) + l2*sin(theta1 + theta2);

    fprintf("Forward kinematics performed.. x1: %f, y1: %f, x2: %f, y2: %f\n", x1, y1, x2, y2);
 
end

% This function calculates the Jacobian at a particular point in space
function J = jacobian_calculate(theta1, theta2, l1, l2)
    J = [(-l1*sin(theta1)-l2*sin(theta1+theta2)) (-l2*sin(theta1 + theta2));
         (l1*cos(theta1)+l2*cos(theta1+theta2)) (l2*cos(theta1 + theta2));];
end

% Used for plotting ellipse
function [] = plot_ellipse(x, y, U, S)
    a = S(1,1)/2;
    b = S(2,2)/2;
    x_center = x;
    y_center = y;
    theta = linspace(0, 2*pi, 1000);
    x = a*cos(theta);
    y = b*sin(theta);
    R = U;
    rotated_coords = R*[x; y;];
    x_rotated = rotated_coords(1, :)';
    y_rotated = rotated_coords(2, :)';
    
    plot(x_center + x_rotated, y_center + y_rotated, 'r');
end

% Used for plotting lines
function [] = plot_lines(x1, x2, y1, y2)
    hold on;
    plot([0 x1], [0 y1], 'b')
    hold on;
    plot([x1 x2], [y1 y2], 'b');
end
