// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// User defined header files
 #include "image_1.h"
 #include "image_2.h" 
 #include "image_3.h" 
 #include "image_4.h" 
 #include "image_5.h" 
 #include "image_6.h" 
 #include "image_7.h" 
 #include "image_8.h" 
 #include "image_9.h" 
 #include "image_10.h"
 #include "image_11.h"
 #include "image_12.h"
 #include "image_13.h"
 #include "image_14.h"
 #include "image_15.h"
 #include "image_16.h"
 #include "image_17.h"
 #include "image_18.h"
 #include "image_19.h"
 #include "image_20.h"
 #include "image_21.h"
 #include "image_22.h"
 #include "image_23.h"
 #include "image_24.h"
 #include "image_25.h"
 #include "image_26.h"
 #include "image_27.h"
 #include "image_28.h"
 #include "image_29.h"
 #include "image_30.h"
 #include "image_31.h"
 #include "image_32.h"
 #include "image_33.h"
 #include "image_34.h"
 #include "image_35.h"
 #include "image_36.h"
 #include "image_37.h"
 #include "image_38.h"
 #include "image_39.h"
 #include "image_40.h"
 #include "image_41.h"
 #include "image_42.h"
 #include "image_43.h"
 #include "image_44.h"
 #include "image_45.h"
 #include "image_46.h"
 #include "image_47.h"
 #include "image_48.h"
 #include "image_49.h"
 #include "image_50.h"
 #include "image_51.h"
 #include "image_52.h"
 #include "image_53.h"
 #include "image_54.h"
 #include "image_55.h"
 #include "image_56.h"
 #include "image_57.h"
 #include "image_58.h"
 #include "image_59.h"
 #include "image_60.h"
 #include "image_61.h"
 #include "image_62.h"
 #include "image_63.h"
 #include "image_64.h"
 #include "image_65.h"
 #include "image_66.h"
 #include "image_67.h"
 #include "image_68.h"
 #include "image_69.h"
 #include "image_70.h"
 #include "image_71.h"
 #include "image_72.h"
 #include "image_73.h"
 #include "image_74.h"
 #include "image_75.h"
 #include "image_76.h"
 #include "image_77.h"
 #include "image_78.h"
 #include "image_79.h"
 #include "image_80.h"
 #include "image_81.h"
 #include "image_82.h"
 #include "image_83.h"
 #include "image_84.h"
 #include "image_85.h"
 #include "image_86.h"
 #include "image_87.h"
 #include "image_88.h"
 #include "image_89.h"
 #include "image_90.h"
 #include "image_91.h"
 #include "image_92.h"
 #include "image_93.h"
 #include "image_94.h"
 #include "image_95.h"
 #include "image_96.h"
 #include "image_97.h"
 #include "image_98.h"
 #include "image_99.h"
 #include "image_100.h"

#include "functions_FE.h"
#include "constants.h"

short (*frames[100]) [810] = 
{arr_out_img_1, arr_out_img_2, arr_out_img_3, arr_out_img_4, arr_out_img_5, arr_out_img_6, arr_out_img_7, arr_out_img_8, arr_out_img_9, arr_out_img_10,
 arr_out_img_11, arr_out_img_12, arr_out_img_13, arr_out_img_14, arr_out_img_15, arr_out_img_16, arr_out_img_17, arr_out_img_18, arr_out_img_19,arr_out_img_20,
 arr_out_img_21, arr_out_img_22, arr_out_img_23, arr_out_img_24, arr_out_img_25, arr_out_img_26, arr_out_img_27, arr_out_img_28, arr_out_img_29, arr_out_img_30,
 arr_out_img_31, arr_out_img_32, arr_out_img_33, arr_out_img_34, arr_out_img_35, arr_out_img_36, arr_out_img_37, arr_out_img_38, arr_out_img_39, arr_out_img_40,
 arr_out_img_41, arr_out_img_42, arr_out_img_43, arr_out_img_44, arr_out_img_45, arr_out_img_46, arr_out_img_47, arr_out_img_48, arr_out_img_49, arr_out_img_50, 
 arr_out_img_51, arr_out_img_52, arr_out_img_53, arr_out_img_54, arr_out_img_55, arr_out_img_56, arr_out_img_57, arr_out_img_58, arr_out_img_59, arr_out_img_60,
 arr_out_img_61, arr_out_img_62, arr_out_img_63, arr_out_img_64, arr_out_img_65, arr_out_img_66, arr_out_img_67, arr_out_img_68, arr_out_img_69, arr_out_img_70,
 arr_out_img_71, arr_out_img_72, arr_out_img_73, arr_out_img_74, arr_out_img_75, arr_out_img_76, arr_out_img_77, arr_out_img_78, arr_out_img_79, arr_out_img_80, 
 arr_out_img_81, arr_out_img_82, arr_out_img_83, arr_out_img_84, arr_out_img_85, arr_out_img_86, arr_out_img_87, arr_out_img_88, arr_out_img_89, arr_out_img_90, 
 arr_out_img_91, arr_out_img_92, arr_out_img_93, arr_out_img_94, arr_out_img_95, arr_out_img_96, arr_out_img_97, arr_out_img_98, arr_out_img_99, arr_out_img_100,};

int main()
{
    int frame = 0;
    int tot_stars = 0;
    double centroids_st[MAX_STARS][3];

    while(frame < 100)
    {
        printf("SIS_iter_%d\n", frame + 1);
        tot_stars = 0;
        regionGrowth(frames[frame], centroids_st, &tot_stars);
        for(int i = 0; i < tot_stars; i++)
        {
            printf("%d %.16f %.16f\n", (int)centroids_st[i][0], centroids_st[i][1], centroids_st[i][2]);
        }
        printf("\n\n");
        frame++;
    }

}