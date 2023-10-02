table = readtable('TM_results.csv');
table_mism = readtable('TM_results_mismatches.csv');
table_Lism = readtable('TM_results_lism_mismatches.csv');

array = table2array(table);
array_mism = table2array(table_mism);
array_Lism = table2array(table_Lism);

x = array(:,1);

cnms_lism = array(:,8);
cnms_tm = array(:,9);

tm_time_ms = array(:,3)*1000;
lism_time_ms = array(:,4)*1000;


figure
hold on
grid on
% title('Comparison of time taken by TM and LISM')
xlabel('Testcase index')
ylabel('Time taken (ms)')
plot(x, tm_time_ms, 'DisplayName','Tracking Mode', 'Marker', '.', 'MarkerSize', 10)
plot(x, lism_time_ms, 'DisplayName','LIS Mode', 'Marker', '*', 'MarkerSize', 5)


legend('TM','LISM', 'Location', 'North')
hold off

figure
hold on
grid on
xlabel('Test index')
ylabel('Number of frames')
plot(x, cnms_tm, 'Marker', '.', 'MarkerSize', 25)
plot(x, cnms_lism, 'Marker', '*', 'MarkerSize', 5)

legend('TM','LISM', 'Location', 'North')
hold off


% tm_time_mean = mean(tm_time_ms);
% lism_time_mean = mean(lism_time_ms);
% coef_of_var_tm = tm_time_std/tm_time_mean;
% coef_of_var_lism = lism_time_std/lism_time_mean;
% tm_time_std = std(tm_time_ms);
% lism_time_std = std(lism_time_ms);

figure 
hold on 
grid on
xlabel('Time taken (ms)')
ylabel('Frequency')

histogram(tm_time_ms, 10,'BinWidth',50, 'Normalization','probability')
histogram(lism_time_ms,10,'BinWidth',50, 'Normalization','probability')
% xline(tm_time_mean, 'Color', 'blue')
% xline(lism_time_mean, 'Color', '#D95319')
% xticks([0 178.32 500 575.18 1000 1500])
% xticklabels({'0', 't_{TM}', '500', 't_{LISM}', '1000', '1500'})
legend('TM','LISM', 'Location', 'North')
hold off

figure
hold on 
grid on
ylabel('Frequency')
xlabel('Difference in Matching Accuracy (in %)')

xlim([-50 50])
% yline(100)
%ylim([50 100])
%plot(array_mism(:,1), array_Lism(:,7)- array_mism(:,7), 'Marker', '.', 'MarkerSize', 10)
histogram(array_Lism(:,7)-array_mism(:,7),83,'BinWidth',2, 'Normalization','probability')
%histogram(array_Lism(:,7),83,'BinWidth',1, 'Normalization','probability')
%plot(array_Lism(:,1), array_Lism(:,7), 'Marker', '*', 'MarkerSize', 5)
acc_std = std(array_Lism(:,7)-array_mism(:,7))
acc_mean = mean(array_Lism(:,7)-array_mism(:,7))
hold off
