for testcase = 1: 83
    N_star_array = []
    for im = 1: 100
        out = zeros(3, 50)
        SIS_output = load(sprintf('../SIS_runs/SIS run-%s/Output/SIS_iter_%s.mat', string(testcase), string(im)))
        data_table = SIS_output.sis_output.data_table
        iner_vecs = data_table.r0
        body_vecs = data_table.r3
        N_star = size(iner_vecs,1)
        if(N_star > 25)
            N_star = 25
            out = [iner_vecs(1:25 ,:); body_vecs(1:25,:)]'
        else
            out_t = [iner_vecs; body_vecs]'
            out(:, 1: 2*N_star) = out_t
        end
        N_star_array = [N_star_array N_star]
%      writematrix(UIS, sprintf('./STADS_Tracking_Mode/Centroids/Testcase_%s/txt/UIS_%s.txt',string(i),string(j)));
        writematrix(out, sprintf('../EST_OILS/Testcase_%s/UIS_Est_%s.txt', string(testcase), string(im)))
    end
    writematrix(N_star_array, sprintf('../EST_OILS/Testcase_%s/Stars_Est_%s.txt', string(testcase), string(testcase)))
end