test_index = []
im_index = []
incorrect_match = []
p = 0
for testcase = 1:83
    for im = 1:100
        matched = []
        MILS_st = load(sprintf('../../FE_MILS/MILS_FE_output/FE_Testcase_%s/RGA/MILS_iter_%s.mat', string(testcase), string(im)))
        MILS = table2array(struct2table(MILS_st.fe_output.centroids))
        OILS_csv = sprintf('../../FE_OILS/Out_FE_csv/out_FE_%s/FE_O_iter_info_%s.csv', string(testcase), string(im))
        OILS_t = readtable(OILS_csv)
        OILS = table2array(OILS_t(:, 2:4))
        if (size(MILS, 1) ~= 0 & size(OILS,1)~= 0)
            for ct_o = 1: size(OILS, 1) 
                for ct_m = 1:size(MILS, 1)
                    dist = sqrt( (MILS(ct_m, 2)-OILS(ct_o, 2))^2 + (MILS(ct_m, 3)-OILS(ct_o, 3))^2 )
                    if(dist < 10e-8)
                        matched = [matched; OILS(ct_o, :)]
                    end
                end
            end 
            if(size(matched, 1) ~= size(OILS, 1))
                incorrect_match = [incorrect_match; testcase im]
            end
            
            if (size(MILS, 1) ~= size(OILS, 1))
                test_index = [test_index; testcase]
                im_index = [im_index; im]
            end
        end
        
        %testcases with more stars identified in MILS over OILS
        
    end    
end    
