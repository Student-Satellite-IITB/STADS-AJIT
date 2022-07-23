// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cortos.h"

// User defined header files
//  #include "image_1.h"
//  #include "image_2.h" 
//  #include "image_3.h" 
//  #include "image_4.h" 
//  #include "image_5.h" 
//  #include "image_6.h" 
//  #include "image_7.h" 
//  #include "image_8.h" 
//  #include "image_9.h" 
//  #include "image_10.h"
//  #include "image_11.h"
//  #include "image_12.h"
//  #include "image_13.h"
//  #include "image_14.h"
//  #include "image_15.h"
//  #include "image_16.h"
//  #include "image_17.h"
//  #include "image_18.h"
//  #include "image_19.h"
//  #include "image_20.h"
//  #include "image_21.h"
//  #include "image_22.h"
//  #include "image_23.h"
//  #include "image_24.h"
//  #include "image_25.h"
//  #include "image_26.h"
//  #include "image_27.h"
//  #include "image_28.h"
//  #include "image_29.h"
//  #include "image_30.h"
//  #include "image_31.h"
//  #include "image_32.h"
//  #include "image_33.h"
//  #include "image_34.h"
//  #include "image_35.h"
//  #include "image_36.h"
//  #include "image_37.h"
//  #include "image_38.h"
//  #include "image_39.h"
//  #include "image_40.h"
//  #include "image_41.h"
//  #include "image_42.h"
//  #include "image_43.h"
//  #include "image_44.h"
//  #include "image_45.h"
//  #include "image_46.h"
//  #include "image_47.h"
//  #include "image_48.h"
//  #include "image_49.h"
//  #include "image_50.h"
//  #include "image_51.h"
//  #include "image_52.h"
//  #include "image_53.h"
//  #include "image_54.h"
//  #include "image_55.h"
//  #include "image_56.h"
//  #include "image_57.h"
//  #include "image_58.h"
//  #include "image_59.h"
//  #include "image_60.h"
//  #include "image_61.h"
//  #include "image_62.h"
//  #include "image_63.h"
//  #include "image_64.h"
//  #include "image_65.h"
//  #include "image_66.h"
//  #include "image_67.h"
//  #include "image_68.h"
//  #include "image_69.h"
//  #include "image_70.h"
//  #include "image_71.h"
//  #include "image_72.h"
//  #include "image_73.h"
//  #include "image_74.h"
//  #include "image_75.h"
//  #include "image_76.h"
//  #include "image_77.h"
//  #include "image_78.h"
//  #include "image_79.h"
//  #include "image_80.h"
//  #include "image_81.h"
//  #include "image_82.h"
//  #include "image_83.h"
//  #include "image_84.h"
//  #include "image_85.h"
//  #include "image_86.h"
//  #include "image_87.h"
//  #include "image_88.h"
//  #include "image_89.h"
//  #include "image_90.h"
//  #include "image_91.h"
//  #include "image_92.h"
//  #include "image_93.h"
//  #include "image_94.h"
//  #include "image_95.h"
//  #include "image_96.h"
//  #include "image_97.h"
//  #include "image_98.h"
//  #include "image_99.h"
//  #include "image_100.h"
// -----------------------------------------------------------------------------------------------------------------------
#include "UIS_0.h"
// #include "UIS_1.h"
// #include "UIS_2.h"
// #include "UIS_3.h"
// #include "UIS_4.h"
// #include "UIS_5.h"
// #include "UIS_6.h"
// #include "UIS_7.h"
// #include "UIS_8.h"
// #include "UIS_9.h"
// #include "UIS_10.h"
// #include "UIS_11.h"
// #include "UIS_12.h"
// #include "UIS_13.h"
// #include "UIS_14.h"
// #include "UIS_15.h"
// #include "UIS_16.h"
// #include "UIS_17.h"
// #include "UIS_18.h"
// #include "UIS_19.h"
// #include "UIS_20.h"
// #include "UIS_21.h"
// #include "UIS_22.h"
// #include "UIS_23.h"
// #include "UIS_24.h"
// #include "UIS_25.h"
// #include "UIS_26.h"
// #include "UIS_27.h"
// #include "UIS_28.h"
// #include "UIS_29.h"
// #include "UIS_30.h"
// #include "UIS_31.h"
// #include "UIS_32.h"
// #include "UIS_33.h"
// #include "UIS_34.h"
// #include "UIS_35.h"
// #include "UIS_36.h"
// #include "UIS_37.h"
// #include "UIS_38.h"
// #include "UIS_39.h"
// #include "UIS_40.h"
// #include "UIS_41.h"
// #include "UIS_42.h"
// #include "UIS_43.h"
// #include "UIS_44.h"
// #include "UIS_45.h"
// #include "UIS_46.h"
// #include "UIS_47.h"
// #include "UIS_48.h"
// #include "UIS_49.h"
// #include "UIS_50.h"
// #include "UIS_51.h"
// #include "UIS_52.h"
// #include "UIS_53.h"
// #include "UIS_54.h"
// #include "UIS_55.h"
// #include "UIS_56.h"
// #include "UIS_57.h"
// #include "UIS_58.h"
// #include "UIS_59.h"
// #include "UIS_60.h"
// #include "UIS_61.h"
// #include "UIS_62.h"
// #include "UIS_63.h"
// #include "UIS_64.h"
// #include "UIS_65.h"
// #include "UIS_66.h"
// #include "UIS_67.h"
// #include "UIS_68.h"
// #include "UIS_69.h"
// #include "UIS_70.h"
// #include "UIS_71.h"
// #include "UIS_72.h"
// #include "UIS_73.h"
// #include "UIS_74.h"
// #include "UIS_75.h"
// #include "UIS_76.h"
// #include "UIS_77.h"
// #include "UIS_78.h"
// #include "UIS_79.h"
// #include "UIS_80.h"
// #include "UIS_81.h"
// #include "UIS_82.h"
// #include "UIS_83.h"
// #include "UIS_84.h"
// #include "UIS_85.h"
// #include "UIS_86.h"
// #include "UIS_87.h"
// #include "UIS_88.h"
// #include "UIS_89.h"
// #include "UIS_90.h"
// #include "UIS_91.h"
// #include "UIS_92.h"
// #include "UIS_93.h"
// #include "UIS_94.h"
// #include "UIS_95.h"
// #include "UIS_96.h"
// #include "UIS_97.h"
// #include "UIS_98.h"
// #include "UIS_99.h"


#include "functions.h"
#include "constants.h"



int sm_K_vec_arr[224792][3];


int main()
{
// cortos_printf("SIS_iter_1\n");
// OILS(arr_out_img_1);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_2\n");
// OILS(UIS_0, CORTOS_N_i_0);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_3\n");
// OILS(arr_out_img_3);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_4\n");
// OILS(arr_out_img_4);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_5\n");
// OILS(arr_out_img_5);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_6\n");
// OILS(arr_out_img_6);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_7\n");
// OILS(arr_out_img_7);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_8\n");
// OILS(arr_out_img_8);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_9\n");
// OILS(arr_out_img_9);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_10\n");
// OILS(arr_out_img_10);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_11\n");
// OILS(arr_out_img_11);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_12\n");
// OILS(arr_out_img_12);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_13\n");
// OILS(arr_out_img_13);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_14\n");
// OILS(arr_out_img_14);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_15\n");
// OILS(arr_out_img_15);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_16\n");
// OILS(arr_out_img_16);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_17\n");
// OILS(arr_out_img_17);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_18\n");
// OILS(arr_out_img_18);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_19\n");
// OILS(arr_out_img_19);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_20\n");
// OILS(arr_out_img_20);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_21\n");
// OILS(arr_out_img_21);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_22\n");
// OILS(arr_out_img_22);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_23\n");
// OILS(arr_out_img_23);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_24\n");
// OILS(arr_out_img_24);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_25\n");
// OILS(arr_out_img_25);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_26\n");
// OILS(arr_out_img_26);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_27\n");
// OILS(arr_out_img_27);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_28\n");
// OILS(arr_out_img_28);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_29\n");
// OILS(arr_out_img_29);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_30\n");
// OILS(arr_out_img_30);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_31\n");
// OILS(arr_out_img_31);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_32\n");
// OILS(arr_out_img_32);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_33\n");
// OILS(arr_out_img_33);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_34\n");
// OILS(arr_out_img_34);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_35\n");
// OILS(arr_out_img_35);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_36\n");
// OILS(arr_out_img_36);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_37\n");
// OILS(arr_out_img_37);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_38\n");
// OILS(arr_out_img_38);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_39\n");
// OILS(arr_out_img_39);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_40\n");
// OILS(arr_out_img_40);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_41\n");
// OILS(arr_out_img_41);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_42\n");
// OILS(arr_out_img_42);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_43\n");
// OILS(arr_out_img_43);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_44\n");
// OILS(arr_out_img_44);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_45\n");
// OILS(arr_out_img_45);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_46\n");
// OILS(arr_out_img_46);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_47\n");
// OILS(arr_out_img_47);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_48\n");
// OILS(arr_out_img_48);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_49\n");
// OILS(arr_out_img_49);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_50\n");
// OILS(arr_out_img_50);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_51\n");
// OILS(arr_out_img_51);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_52\n");
// OILS(arr_out_img_52);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_53\n");
// OILS(arr_out_img_53);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_54\n");
// OILS(arr_out_img_54);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_55\n");
// OILS(arr_out_img_55);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_56\n");
// OILS(arr_out_img_56);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_57\n");
// OILS(arr_out_img_57);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_58\n");
// OILS(arr_out_img_58);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_59\n");
// OILS(arr_out_img_59);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_60\n");
// OILS(arr_out_img_60);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_61\n");
// OILS(arr_out_img_61);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_62\n");
// OILS(arr_out_img_62);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_63\n");
// OILS(arr_out_img_63);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_64\n");
// OILS(arr_out_img_64);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_65\n");
// OILS(arr_out_img_65);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_66\n");
// OILS(arr_out_img_66);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_67\n");
// OILS(arr_out_img_67);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_68\n");
// OILS(arr_out_img_68);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_69\n");
// OILS(arr_out_img_69);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_70\n");
// OILS(arr_out_img_70);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_71\n");
// OILS(arr_out_img_71);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_72\n");
// OILS(arr_out_img_72);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_73\n");
// OILS(arr_out_img_73);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_74\n");
// OILS(arr_out_img_74);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_75\n");
// OILS(arr_out_img_75);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_76\n");
// OILS(arr_out_img_76);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_77\n");
// OILS(arr_out_img_77);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_78\n");
// OILS(arr_out_img_78);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_79\n");
// OILS(arr_out_img_79);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_80\n");
// OILS(arr_out_img_80);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_81\n");
// OILS(arr_out_img_81);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_82\n");
// OILS(arr_out_img_82);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_83\n");
// OILS(arr_out_img_83);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_84\n");
// OILS(arr_out_img_84);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_85\n");
// OILS(arr_out_img_85);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_86\n");
// OILS(arr_out_img_86);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_87\n");
// OILS(arr_out_img_87);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_88\n");
// OILS(arr_out_img_88);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_89\n");
// OILS(arr_out_img_89);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_90\n");
// OILS(arr_out_img_90);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_91\n");
// OILS(arr_out_img_91);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_92\n");
// OILS(arr_out_img_92);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_93\n");
// OILS(arr_out_img_93);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_94\n");
// OILS(arr_out_img_94);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_95\n");
// OILS(arr_out_img_95);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_96\n");
// OILS(arr_out_img_96);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_97\n");
// OILS(arr_out_img_97);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_98\n");
// OILS(arr_out_img_98);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_99\n");
// OILS(arr_out_img_99);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_100\n");
// OILS(arr_out_img_100);
// cortos_printf("\n\n\n");
// -------------------------------------------------------------------------------------------------------------------
cortos_printf("SIS_iter_0\n");
OILS(UIS_0, CORTOS_N_i_0);
cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_1\n");
// OILS(UIS_1, CORTOS_N_i_1);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_2\n");
// OILS(UIS_2, CORTOS_N_i_2);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_3\n");
// OILS(UIS_3, CORTOS_N_i_3);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_4\n");
// OILS(UIS_4, CORTOS_N_i_4);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_5\n");
// OILS(UIS_5, CORTOS_N_i_5);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_6\n");
// OILS(UIS_6, CORTOS_N_i_6);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_7\n");
// OILS(UIS_7, CORTOS_N_i_7);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_8\n");
// OILS(UIS_8, CORTOS_N_i_8);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_9\n");
// OILS(UIS_9, CORTOS_N_i_9);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_10\n");
// OILS(UIS_10, CORTOS_N_i_10);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_11\n");
// OILS(UIS_11, CORTOS_N_i_11);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_12\n");
// OILS(UIS_12, CORTOS_N_i_12);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_13\n");
// OILS(UIS_13, CORTOS_N_i_13);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_14\n");
// OILS(UIS_14, CORTOS_N_i_14);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_15\n");
// OILS(UIS_15, CORTOS_N_i_15);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_16\n");
// OILS(UIS_16, CORTOS_N_i_16);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_17\n");
// OILS(UIS_17, CORTOS_N_i_17);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_18\n");
// OILS(UIS_18, CORTOS_N_i_18);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_19\n");
// OILS(UIS_19, CORTOS_N_i_19);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_20\n");
// OILS(UIS_20, CORTOS_N_i_20);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_21\n");
// OILS(UIS_21, CORTOS_N_i_21);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_22\n");
// OILS(UIS_22, CORTOS_N_i_22);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_23\n");
// OILS(UIS_23, CORTOS_N_i_23);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_24\n");
// OILS(UIS_24, CORTOS_N_i_24);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_25\n");
// OILS(UIS_25, CORTOS_N_i_25);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_26\n");
// OILS(UIS_26, CORTOS_N_i_26);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_27\n");
// OILS(UIS_27, CORTOS_N_i_27);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_28\n");
// OILS(UIS_28, CORTOS_N_i_28);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_29\n");
// OILS(UIS_29, CORTOS_N_i_29);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_30\n");
// OILS(UIS_30, CORTOS_N_i_30);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_31\n");
// OILS(UIS_31, CORTOS_N_i_31);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_32\n");
// OILS(UIS_32, CORTOS_N_i_32);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_33\n");
// OILS(UIS_33, CORTOS_N_i_33);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_34\n");
// OILS(UIS_34, CORTOS_N_i_34);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_35\n");
// OILS(UIS_35, CORTOS_N_i_35);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_36\n");
// OILS(UIS_36, CORTOS_N_i_36);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_37\n");
// OILS(UIS_37, CORTOS_N_i_37);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_38\n");
// OILS(UIS_38, CORTOS_N_i_38);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_39\n");
// OILS(UIS_39, CORTOS_N_i_39);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_40\n");
// OILS(UIS_40, CORTOS_N_i_40);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_41\n");
// OILS(UIS_41, CORTOS_N_i_41);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_42\n");
// OILS(UIS_42, CORTOS_N_i_42);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_43\n");
// OILS(UIS_43, CORTOS_N_i_43);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_44\n");
// OILS(UIS_44, CORTOS_N_i_44);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_45\n");
// OILS(UIS_45, CORTOS_N_i_45);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_46\n");
// OILS(UIS_46, CORTOS_N_i_46);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_47\n");
// OILS(UIS_47, CORTOS_N_i_47);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_48\n");
// OILS(UIS_48, CORTOS_N_i_48);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_49\n");
// OILS(UIS_49, CORTOS_N_i_49);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_50\n");
// OILS(UIS_50, CORTOS_N_i_50);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_51\n");
// OILS(UIS_51, CORTOS_N_i_51);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_52\n");
// OILS(UIS_52, CORTOS_N_i_52);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_53\n");
// OILS(UIS_53, CORTOS_N_i_53);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_54\n");
// OILS(UIS_54, CORTOS_N_i_54);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_55\n");
// OILS(UIS_55, CORTOS_N_i_55);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_56\n");
// OILS(UIS_56, CORTOS_N_i_56);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_57\n");
// OILS(UIS_57, CORTOS_N_i_57);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_58\n");
// OILS(UIS_58, CORTOS_N_i_58);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_59\n");
// OILS(UIS_59, CORTOS_N_i_59);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_60\n");
// OILS(UIS_60, CORTOS_N_i_60);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_61\n");
// OILS(UIS_61, CORTOS_N_i_61);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_62\n");
// OILS(UIS_62, CORTOS_N_i_62);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_63\n");
// OILS(UIS_63, CORTOS_N_i_63);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_64\n");
// OILS(UIS_64, CORTOS_N_i_64);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_65\n");
// OILS(UIS_65, CORTOS_N_i_65);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_66\n");
// OILS(UIS_66, CORTOS_N_i_66);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_67\n");
// OILS(UIS_67, CORTOS_N_i_67);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_68\n");
// OILS(UIS_68, CORTOS_N_i_68);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_69\n");
// OILS(UIS_69, CORTOS_N_i_69);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_70\n");
// OILS(UIS_70, CORTOS_N_i_70);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_71\n");
// OILS(UIS_71, CORTOS_N_i_71);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_72\n");
// OILS(UIS_72, CORTOS_N_i_72);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_73\n");
// OILS(UIS_73, CORTOS_N_i_73);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_74\n");
// OILS(UIS_74, CORTOS_N_i_74);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_75\n");
// OILS(UIS_75, CORTOS_N_i_75);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_76\n");
// OILS(UIS_76, CORTOS_N_i_76);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_77\n");
// OILS(UIS_77, CORTOS_N_i_77);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_78\n");
// OILS(UIS_78, CORTOS_N_i_78);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_79\n");
// OILS(UIS_79, CORTOS_N_i_79);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_80\n");
// OILS(UIS_80, CORTOS_N_i_80);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_81\n");
// OILS(UIS_81, CORTOS_N_i_81);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_82\n");
// OILS(UIS_82, CORTOS_N_i_82);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_83\n");
// OILS(UIS_83, CORTOS_N_i_83);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_84\n");
// OILS(UIS_84, CORTOS_N_i_84);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_85\n");
// OILS(UIS_85, CORTOS_N_i_85);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_86\n");
// OILS(UIS_86, CORTOS_N_i_86);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_87\n");
// OILS(UIS_87, CORTOS_N_i_87);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_88\n");
// OILS(UIS_88, CORTOS_N_i_88);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_89\n");
// OILS(UIS_89, CORTOS_N_i_89);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_90\n");
// OILS(UIS_90, CORTOS_N_i_90);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_91\n");
// OILS(UIS_91, CORTOS_N_i_91);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_92\n");
// OILS(UIS_92, CORTOS_N_i_92);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_93\n");
// OILS(UIS_93, CORTOS_N_i_93);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_94\n");
// OILS(UIS_94, CORTOS_N_i_94);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_95\n");
// OILS(UIS_95, CORTOS_N_i_95);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_96\n");
// OILS(UIS_96, CORTOS_N_i_96);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_97\n");
// OILS(UIS_97, CORTOS_N_i_97);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_98\n");
// OILS(UIS_98, CORTOS_N_i_98);
// cortos_printf("\n\n\n");


// cortos_printf("SIS_iter_99\n");
// OILS(UIS_99, CORTOS_N_i_99);
// cortos_printf("\n\n\n");
    
    cortos_exit(0);
}