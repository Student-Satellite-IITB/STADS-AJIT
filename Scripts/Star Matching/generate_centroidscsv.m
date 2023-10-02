UIS_LENGTH = [0]
for i = 1 : 83 
    for j = 1 : 100
        sis_iter = load(sprintf('../SIS_runs/SIS run-%s/Output/SIS_iter_%s.mat',string(i), string(j)));

        CENT = sis_iter.sis_output.data_table;
        UIS = [CENT.SSP_ID CENT.Sensor_y CENT.Sensor_z]
        UIS_final = UIS(find(CENT.SSP_ID < 8876), :)
        UIS_LENGTH = [UIS_LENGTH, length(UIS_final)]

%         writematrix(UIS_final, sprintf('STADS_Tracking_Mode/Centroids/Taurus-1/txt/UIS_%s.txt',string(j)));
        writematrix(UIS, sprintf('./STADS_Tracking_Mode/Centroids/Testcase_%s/txt/UIS_%s.txt',string(i),string(j)));
    end
end

%%________To_find_average_no._of_stars_in_the_image____________%%
avg = 0;
for i = 2 : 8301
    avg = avg + UIS_LENGTH(i);
end
average_stars = avg/8300

array = []
for i = 1 : 83
    array = [array; UIS_LENGTH(2+100*i : 101+100*i)]
end
writematrix(array, 'N_stars_in_image.txt');
