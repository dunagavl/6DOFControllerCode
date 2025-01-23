% Define the data
x = [0, 80, 153, 242, 319, 409, 478, 574, 655, 737, 816, 890, 981, 1069, 1147, 1233, ...
     1326, 1408, 1488, 1567, 1652, 1730, 1815, 1887, 1968, 2045, 2137, 2215, 2278, 2353, ...
     2434, 2517, 2601, 2671, 2750, 2833, 2912, 2990, 3066, 3155, 3245, 3328, 3435, 3530, ...
     3652, 3769, 3889, 4009, 4095];
y = [0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, ...
     100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, ...
     180, 185, 190, 195, 200, 205, 210, 215, 220, 225, 230, 235, 240];

% Calculate the piecewise linear model using differences
slopes = diff(y) ./ diff(x);
intercepts = y(1:end-1) - slopes .* x(1:end-1);

% Initialize simplified segments
simplified_slopes = [];
simplified_intercepts = [];
simplified_start = x(1);
simplified_end = [];

% Simplify the segments by combining those with the same slope and intercept
for i = 2:length(slopes)
    if slopes(i) ~= slopes(i-1) || intercepts(i) ~= intercepts(i-1)
        simplified_slopes = [simplified_slopes; slopes(i-1)];
        simplified_intercepts = [simplified_intercepts; intercepts(i-1)];
        simplified_end = [simplified_end; x(i)];
        simplified_start = [simplified_start; x(i)];
    end
end
% Add the last segment
simplified_slopes = [simplified_slopes; slopes(end)];
simplified_intercepts = [simplified_intercepts; intercepts(end)];
simplified_end = [simplified_end; x(end)];

% Display each line equation for simplified segments
disp('Simplified Piecewise Linear Segment Equations:');
for i = 1:length(simplified_slopes)
    fprintf('Segment from %d to %d: y = %.4fx + %.4f\n', simplified_start(i), simplified_end(i), simplified_slopes(i), simplified_intercepts(i));
end

% Plot the data and the original piecewise fit
figure;
plot(x, y, 'bo', 'DisplayName', 'Actual Data');
hold on;

% Plot each simplified segment
for i = 1:length(simplified_slopes)
    plot([simplified_start(i), simplified_end(i)], [simplified_start(i) * simplified_slopes(i) + simplified_intercepts(i), simplified_end(i) * simplified_slopes(i) + simplified_intercepts(i)], 'r-', 'LineWidth', 2);
end
title('Optimized Piecewise Linear Fit to Data');
xlabel('Digital Output');
ylabel('Degrees');
legend('show');
grid on;
