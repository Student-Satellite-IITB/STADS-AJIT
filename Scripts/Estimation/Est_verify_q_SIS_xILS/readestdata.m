table = readtable("CoRTOS_OUTPUTS/OUTPUT_13_6.5/readings.csv");
estoutput = table2array(table);

final_error = zeros(100,4);
for i = 1:100
es_output = estoutput(i,1:4);
inputfile = "matout_run13_6.5/SIS_iter_" + i + ".mat";
load(inputfile);
disp("SIS_iter_" + i);
final_error(i,1:4) = sim_error(sis_input_attitude, es_output');
end
 disp("The maximum values for error quaternions are:")
 disp(final_error(:,4));


% norm_final_error = zeros(100,1);
% for i=1:100
% norm_final_error(i,1) = norm(final_error(i, 1:3));
% end

%mean_max_error = mean(final_error(:,4));
%mean_norm_error = mean(norm_final_error);


%subplot(2,1,1)

%histogram(final_error(:,4), 'Facecolor', 'cyan', 'NumBins', 20,  'LineWidth', 0.75);
% xline(0.1707, 'r', 'mean = 0.1707', 'LabelOrientation', 'aligned', 'LabelHorizontalAlignment', 'left');
% xlim([0, 0.4])
% ylim([0,15]);
% title("Distribution of number of images as a function of maximum error in attitude")
% xlabel("Maximum error (in arcsec)")
% ylabel("Number of images")




% subplot(2,1,2)
% histogram(norm_final_error, 'Facecolor', 'cyan', 'NumBins', 20, 'LineWidth', 0.75);
% xline(0.1990, 'r', 'mean = 0.1990', 'LabelOrientation', 'aligned', 'LabelHorizontalAlignment', 'left');
% xlim([0, 0.4])
% ylim([0,20]);
% title("Distribution of number of images as a function of norm of error in attitude")
% xlabel("Average error (in arcsec)")
% ylabel("Number of images")


