% modelwahfilters.m
% Model measured magnitude transfer functions from wah pedal with peaking
% filters

load wahtransferfunctions.mat

% wahtransferfunctions.mat includes the following variables:
% tfs   % Frequency responses (FFTs) of 11 wah pedal settings
% fs    % Sampling rate at which measurements were made (44.1k)
% pedal % Vector containing pedal positions at which measurements were made
% freq  % Vector of frequencies at which responses were measured

measurementnumber=1;
pedalposition=pedal(measurementnumber);
%%% Plot dB response of pedal at measured position (measurementnumber):
%%% 11 positions measured, so measurementnumber must be between 1, 11.
%%% ***NOTE THAT THE RESPONSE DOES NOT CHANGE FOR THE FIRST SEVERAL
%%% PEDAL POSITIONS MEASURED!!*************************************

figure(1)
semilogx(freq,20*log10(abs(tfs(:,measurementnumber))),'b','LineWidth',2)
grid on
axis([20,20000,-30,10])  %Limit axes to 20-20k Hz
xlabel('Frequency, Hz')
ylabel('Magnitude Response, dB')
% text(30,2,'Measured','Color','Blue','FontSize',15)
% text(30,2,'Model','Color','black','FontSize',15)
% thestr=strcat('Pedal Position=',num2str(pedalposition));
title('Wah Pedal at 11 Positions');

%%%%%%%%%%%%% Peaking filter definition %%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%               gamma*s/w0
% H(s) = __________________________
%         s^2/w0^2 + s/(w0*Q) + 1
%

%%$ Starter Code
%%% Choose gamma, f0, Q to match each of the 11 wah pedal responses.
% gamma = 0.15;             % gamma*Q = peak gain
% f0 = 400;               % f0 = center freq, Hz
% w0 = f0*2*pi;            % w0 in radians/sec
% Q = 15.0;                 % Q = resonance
% 
% 
% b=[0          gamma/w0  0];
% a=[1/(w0*w0)  1/(w0*Q)  1];
% [bz,az]=bilinear(b,a,fs,f0);  % Bilinear transform for sampling rate fs,
%                               % warping response to match at f0.
% H=freqz(bz,az,8192);          % Calculate response of digital filter
% zfreq=linspace(0,fs/2,8192);  % frequency axis for plotting
% hold on
% semilogx(zfreq,20*log10(abs(H)),'r')
% hold off

%%%

figure(1)
hold on
colors = jet(11); % Generate 11 distinct colors

% Define arrays for gamma, f0, Q with individual editable values for each pedal position
gammas = [0.15, 0.15, 0.15, 0.18, 0.19, 0.28, 0.42, 0.55, 0.63, 0.74, 0.87]; 
f0s =    [400,   400,  400,  405,  500,  650, 1010, 1200, 1450, 1750, 2000]; 
Qs =     [15.0, 15.0, 15.0, 11.0,  10.0,  7.0, 5.0,  4.0, 3.5,  3.0,  2.6];

for measurementnumber = 1:11
    pedalposition = pedal(measurementnumber);

    % Use distinct gamma, f0, Q for each pedal position
    gamma = gammas(measurementnumber);
    f0 = f0s(measurementnumber);
    w0 = f0*2*pi;
    Q = Qs(measurementnumber);

    % Plot measured response
    semilogx(freq, 20*log10(abs(tfs(:,measurementnumber))), 'Color', colors(measurementnumber,:), 'LineWidth', 2)

    % Define filter and calculate response
    b = [0, gamma/w0, 0];
    a = [1/(w0*w0), 1/(w0*Q), 1];
    [bz, az] = bilinear(b, a, fs, f0);
    H = freqz(bz, az, 8192);
    zfreq = linspace(0, fs/2, 8192);

    % Plot model response with striped line
    semilogx(zfreq, 20*log10(abs(H)), 'Color', 'black', 'LineStyle', '--')
end

hold off
grid on
axis([20, 20000, -30, 10])  % Limit axes to 20-20k Hz
xlabel('Frequency, Hz')
ylabel('Magnitude Response, dB')
title('Wah Pedal at 11 Positions')


