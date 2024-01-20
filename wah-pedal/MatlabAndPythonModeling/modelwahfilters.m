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
% text(2000,2,'Model','Color','Red','FontSize',15)
% thestr=strcat('Pedal Position=',num2str(pedalposition));
title('Wah Pedal at 11 Positions');

%%%%%%%%%%%%% Peaking filter definition %%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%               gamma*s/w0
% H(s) = __________________________
%         s^2/w0^2 + s/(w0*Q) + 1
%

%%% Choose gamma, f0, Q to match each of the 11 wah pedal responses.
gamma = 0.15;             % gamma*Q = peak gain
f0 = 400;               % f0 = center freq, Hz
w0 = f0*2*pi;            % w0 in radians/sec
Q = 15.0;                 % Q = resonance


b=[0          gamma/w0  0];
a=[1/(w0*w0)  1/(w0*Q)  1];
[bz,az]=bilinear(b,a,fs,f0);  % Bilinear transform for sampling rate fs,
                              % warping response to match at f0.
H=freqz(bz,az,8192);          % Calculate response of digital filter
zfreq=linspace(0,fs/2,8192);  % frequency axis for plotting
hold on
semilogx(zfreq,20*log10(abs(H)),'r')
hold off

%%%

