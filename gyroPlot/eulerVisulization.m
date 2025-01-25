close all;
clear;

global v;
global p;

% Clear any existing serial ports
delete(serialportfind);

% Allow the user to input the port
serialportlist("available");
selectedPort = input("Enter the port you would like to use: ", "s");

% Use the user input to define the Arduino object
arduinoBoard = serialport(selectedPort, 115200); % Set to your device's baud rate

% Prep the object for data streaming 
configureTerminator(arduinoBoard, "CR/LF");
flush(arduinoBoard);

% Setup the figure for plotting
fig = figure;

% Draw a cube for 3D visualization
[v, f] = createCube();
p = patch('Faces', f, 'Vertices', v, 'FaceColor', 'red', 'EdgeColor', 'black', 'FaceAlpha', 0.8);
axis equal;
xlabel('X-axis');
ylabel('Y-axis');
zlabel('Z-axis');
view(3);
grid on;

% Configure the callback function to handle the incoming data
configureCallback(arduinoBoard, "terminator", @readOrientationData);

% Function to create cube data
function [v, f] = createCube
    l = 1; % length of the cube
    v = [-1 -1 -1; 1 -1 -1; 1 1 -1; -1 1 -1; -1 -1 1; 1 -1 1; 1 1 1; -1 1 1]*l/2;
    f = [1 2 3 4; 2 6 7 3; 4 3 7 8; 1 5 8 4; 1 2 6 5; 5 6 7 8];
end

% Callback function to read orientation data
function readOrientationData(src, ~)
    global p;
    global v;
    
    newReading = readline(src);
    disp(['Received data: ', newReading]);  % Debugging output
    dataValues = str2double(strsplit(newReading)); % Assumes space-delimited data

    if length(dataValues) == 4
        disp(['Parsed quaternion values: ', num2str(dataValues)]);  % Display parsed data
        R = quat2rotm(dataValues);
        newVertices = (R * v')'; % Rotate vertices
        set(p, 'Vertices', newVertices);
        drawnow;
    else
        disp('Error in data format or incomplete data received');
    end
end
