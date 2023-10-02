% for testcase = [16 24 25 36 41 54 56 59 60]
for testcase = 1: 83
       table = readtable(sprintf('../EST_OILS_1..83/out_Quest_csv/out_Quest_%s.csv', string(testcase)))
       est_mils = load(sprintf('../Est_MILS/Readings/Est_out_testcase_%s.mat', string(testcase)))
%     table = readtable("quest_100.csv")
    es_output = table2array(table)
    es_output = es_output(:, 1:4)

    final_error = zeros(100,4);
    for i = 1:100
        inputfile = load("../SIS_runs/SIS run-"+ testcase+"/Output/SIS_iter_" + i + ".mat");
%         inputfile = load(sprintf('E:/Github/STADS_GNC/SIS_run/Output/SIS_iter_%s.mat', string(i)))
        if(est_mils.es_out_testcase(i,2) == -1) 
            final_error(i, :) = [0 0 0 0];
        else
            final_error(i,:) = sim_error(inputfile.sis_input_attitude, es_output(i,1:4)');
        end
    end
     disp("The maximum values for error quaternions are:")
     disp(final_error(:,4));
    
    
     norm_final_error = zeros(100,1);
     for i=1:100
         norm_final_error(i,1) = norm(final_error(i, 1:3));
     end
    
    mean_max_error = mean(final_error(:,4));
    mean_norm_error = mean(norm_final_error);
    
    
    subplot(2,1,1)
    
    histogram(final_error(:,4), 'Facecolor', 'cyan', 'NumBins', 20,  'LineWidth', 0.75);
    xline(0.1707, 'r', 'mean = 0.1707', 'LabelOrientation', 'aligned', 'LabelHorizontalAlignment', 'left');
%     xlim([0, 0.4])
%     ylim([0,15]);
     title("Distribution of number of images as a function of maximum error in attitude")
     xlabel("Maximum error (in arcsec)")
     ylabel("Number of images")
    
    
    
     subplot(2,1,2)
     histogram(norm_final_error, 'Facecolor', 'cyan', 'NumBins', 20, 'LineWidth', 0.75);
     xline(0.1990, 'r', 'mean = 0.1990', 'LabelOrientation', 'aligned', 'LabelHorizontalAlignment', 'left');
%      xlim([0, 0.4])
%      ylim([0,20]);
     title("Distribution of number of images as a function of norm of error in attitude")
     xlabel("Average error (in arcsec)")
     ylabel("Number of images")

     exportgraphics(gca, sprintf('final_error_%s.png', string(testcase)))

end


