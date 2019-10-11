arduinoComPort = 'COM5';
baudRate = 9600;
%fclose(instrfind({'Port','Status'},{arduinoComPort,'open'}));
% serialPort = serial(arduinoComPort, baudRate, "Timeout",5);
%data = readln(s,'uint16');
serialPort = serial(arduinoComPort, 'BAUD', baudRate);
fopen(serialPort); 
fprintf(serialPort, '\n');


timeout = 0;
data = [];
fscanf(serialPort);
while timeout < 5
    % check if data was received
    while serialPort.BytesAvailable > 0

        timeout = 0; % reset timeout
        values = eval(strcat('[',fscanf(serialPort),']')); % data was received, convert it into array of integers
        left_sensor = values(1);
        left_speed = values(2);        
        right_sensor = values(3);
        right_speed = values(4);
        data = [data; left_sensor, left_speed, right_sensor, right_speed];
        
    end
    pause(0.5);
    timeout = timeout + 1;
end
disp(data)
save("dataset.mat", "data") %PAN DATA SAVED
%%
time = []; 
for i = 1:1:2156 
    time = [time, i./50];
end
%%
figure(1);
hold on;

title('LEFT SENSOR VS SPEED')
yyaxis left;
ylabel('Left IR Sensor Data')
ylim([700 1000])

xlabel('Time (s)')
plot(time(1:500), data(1:500,1))
hline = refline(0, 850);
hline.Color = 'g';
hline.LineWidth = 3;

yyaxis right;
ylabel('Left Wheel Speed')
ylim([-5 65])

plot(time(1:500), data(1:500,2))

hold off;
%%
figure(2);
hold on;

title('RIGHT SENSOR VS SPEED')
yyaxis left;
ylabel('Right IR Sensor Data')
ylim([700 1000])

xlabel('Time (s)')
plot(time(1:500), data(1:500,3))
hline = refline(0, 850);
hline.Color = 'g';
hline.LineWidth = 3;

yyaxis right; 
ylabel('Right Wheel Speed')
ylim([-5 65])
plot(time(1:500), data(1:500,4))
hold off; 

%plot(data(:,1), data(:,2), '*')

%%

