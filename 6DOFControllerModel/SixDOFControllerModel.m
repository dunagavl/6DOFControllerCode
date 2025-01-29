close all;
clear;
global quat;
global robot;
global ax1;
global ax2;
global p;
global v;

% Setup the serial connection and terminator
s = serialport("COM7", 115200);
configureTerminator(s, "CR/LF");
flush(s);

% Construct the rigid body of the robot
robot = loadrobot("kinovaJacoJ2N6S200");

% Initialize figure
quat = [1 0 0 0]; % Initialize quaternion to identity
figure;
ax1 = subplot(1,2,1);
show(robot, 'Parent', ax1);
hold(ax1, 'on');
title('Robot Configuration');

ax2 = subplot(1,2,2);
[v, f] = createPen();  % Create the pen shape
p = patch('Faces', f, 'Vertices', v, 'FaceColor', 'blue', 'EdgeColor', 'none', 'FaceAlpha', 0.8, 'Parent', ax2);
axis(ax2, 'equal');
title('Quaternion Orientation');
view(ax2, 3);
grid on;

% Configure the callback function to handle the incoming data
configureCallback(s, "terminator", @readPositionData);

% Callback function to read orientation data
function readPositionData(src, ~)
    global quat;
    global robot;
    global ax1;
    global ax2;
    global p;
    global v;
    
    
    data = readline(src);
    disp(['Received data: ', data]);  % Debugging output
    values = str2double(strsplit(data)); % Assumes space-delimited data

    if numel(values) == 7
        joints_deg = values(1:3);
        quat = values(4:7);
        quat = normalizeQuaternion(quat);
        joints_rad = deg2rad(joints_deg);
        
        % Check if the figure and axes are still valid
        if isvalid(ax1) && isvalid(ax2)
            % Clear previous robot configurations
            cla(ax1);  % Clear the robot subplot to ensure only the latest configuration is shown

            % Update robot configuration
            config = homeConfiguration(robot);
            config(3).JointPosition = joints_rad(1);
            config(4).JointPosition = joints_rad(2);
            config(5).JointPosition = joints_rad(3);
            
            % Visualize robot
            show(robot, config, 'Parent', ax1);
            
            % Update pen orientation
            R = quat2rotm(quat);
            newVertices = (R * v')'; % Rotate vertices based on quaternion
            set(p, 'Vertices', newVertices);
            drawnow;
        else
            close all;
            figure;

            % Subplot for robot configuration
            ax1 = subplot(1,2,1);
            show(robot, 'Parent', ax1);
            hold(ax1, 'on');
            title('Robot Configuration');

            % Subplot for quaternion orientation (the pen)
            ax2 = subplot(1,2,2);
            p = patch('Faces', f, 'Vertices', v, 'FaceColor', 'blue', 'EdgeColor', 'none', 'FaceAlpha', 0.8, 'Parent', ax2);
            axis(ax2, 'equal');
            xlabel('X-axis');
            ylabel('Y-axis');
            zlabel('Z-axis');
            title('Stylus Orientation');
            view(ax2, 3);
            grid on;
        end
    end
end

function q_normalized = normalizeQuaternion(q)
    % Calculate the norm of the quaternion
    norm_q = sqrt(sum(q.^2));
    
    % Normalize the quaternion
    if norm_q ~= 0
        q_normalized = q / norm_q;
    else
        q_normalized = q; % Return original if norm is zero to avoid division by zero
    end
end

function [v, f] = createPen()
    [X, Y, Z] = cylinder([0.05, 0.05], 20);  % Cylinder for the pen body
    Z = Z * 5;  % Scale cylinder length
    [X2, Y2, Z2] = cylinder([0.05, 0], 20);  % Cone for the pen tip
    Z2 = Z2 * 2 - 2;  % Position the tip at one end
    X = [X; X2];
    Y = [Y; Y2];
    Z = [Z; Z2 + max(Z(:))];  % Adjust cone position to connect to cylinder
    v = [X(:), Y(:), Z(:)];  % Combine all vertices
    f = convhull(v);  % Create a convex hull of all vertices
end