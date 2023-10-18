import numpy as np
import pygad
import subprocess


import warnings
warnings.filterwarnings('ignore')
min_fitness=1000
best_parameters=[0,0,0,0,0,0]
# Define the number of constants (genes) to generate number of
num_constants = 1

# Define the gene bounds
gene_bounds = [
    # np.linspace(2.088526608657631e-15*0.9,2.088526608657631e-15*1.1),  # epsilon 
    # np.linspace(0.0000938157177559363*0.9,0.0000938157177559363*1.1),  # delta
    np.linspace(2.3e-5, 2.6e-5) 
    # np.linspace(0.1,1) #TOL
    # np.linspace(25,50) #P1
    # np.linspace(70,90) #P2
    # np.linspace(0.004, 0.006) #EPSILON_SEQ_ERROR 
]


    # Define the target outputs
desired_outputs = np.loadtxt("ideal_quat.txt", dtype=float)
desired_outputs = desired_outputs.reshape(100, 4)
    #print(desired_outputs)

    # Define the C program command
c_program_command_1 = "gcc main.c  -o exe -lm"
c_program_command_2 = "./exe"
    
    # Convert gene_bounds to a np array
gene_space = np.array(gene_bounds)


    # Define the fitness function
def fitness_func(ga_instance, solution, solution_idx):
    #
    # solution = solution[:num_constants]
    
        # Generate random values for each gene within the bounds
        #solution = np.random.uniform(low=gene_bounds[0][0], high=gene_bounds[0][1])
        #for i in range(1, num_constants):
        #    solution = np.append(solution, np.random.uniform(low=gene_bounds[i][0], high=gene_bounds[i][1]))
    

        # Save the solution's genes in a header file as constants
    with open("constants.h", "w") as file:
         file.write("#include <stdio.h>\n")
         file.write("#include <stdlib.h>\n")
         file.write("#include <math.h>\n")
         file.write("#include <string.h>\n")
          # Generate multiple constants based on the solution's genes
         #file.write("#define THRESHOLD 3\n")
         file.write("#define STAR_MIN_PIXEL 3\n")
         file.write("#define STAR_MAX_PIXEL 150\n")
         file.write("#define MAX_STARS 100\n")
         file.write("#define SKIP_PIXELS 2\n")
         file.write("#define LENGTH 1216\n")
         file.write("#define BREADTH 916\n")     
         file.write("#define PIXEL_WIDTH 0.00000155\n")
         file.write("#define NUM_MAX_STARS 13\n")
         file.write("//SM constants\n")
         file.write("#define FOCAL_LENGTH 0.0175\n")
         file.write("#define EPSILON 2.2e-15\n")
        #  file.write("#define EPSILON {}\n".format(solution[0]))
         file.write("#define DELTA {}\n".format(solution[0]))
         file.write("#define ANG_DIST_TOLERANCE 1.2\n")
         file.write("#define N_GC 8876\n")
         file.write("#define N_KVEC_PAIRS 224792\n")
         file.write("#define Y_MAX 0.9999999999926209\n")
         file.write("#define Y_MIN 0.9900261208247870\n")
         file.write("#define TOL 0.5\n")
         file.write("#define P1 35\n")
         file.write("#define P2 80\n")
         file.write("#define EPSILON_SEQ_ERROR 0.005\n") 
         file.write("#define EPSILON_EST 0.001 \n")
   # Evaluate the fitness for each test case
      # Run the C program and collect the output
    result = subprocess.run(c_program_command_1, shell=True, capture_output=True, text=True)
    process = subprocess.Popen(c_program_command_2, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
      #process = subprocess.Popen(c_program_command_2, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    output = output.decode().strip()
    # print("EPSILON:", solution[0]," DELTA:", solution[1], " TOL:",solution[2], " P1:",solution[3], " P2:",solution[4], " EsE:",solution[5] )
    print("DELTA:", solution[0])
    print("Output:", output)
    output = list(filter(None, output.split('\n')))
    # Calculate the fitness based on the differences between desired and obtained coordinates
    output_coordinates = np.array([list(map(float, line.split())) for line in output])

    print(desired_outputs.shape)
    print(output_coordinates.shape)
        # Check the shapes of the arrays
    if desired_outputs.shape != output_coordinates.shape:
        raise ValueError("Shape mismatch between desired_outputs and output_coordinates")

        # Calculate the fitness based on the differences between desired and obtained coordinates
       # fitness = np.sum(np.abs(desired_outputs - output_coordinates))
        #fitness=np.abs(sim_error(desired_outputs,output_coordinates))
    fitness=0
    for i in range(desired_outputs.shape[0]):
         desired_row = desired_outputs[i, :]
         obtained_row = output_coordinates[i, :]
         fitness += np.sum(np.linalg.norm(desired_row - obtained_row))
    print(1/fitness)
    global min_fitness
    if fitness < min_fitness:
        
        for i in range(num_constants):       
            best_parameters[i]=solution[i]
        min_fitness=fitness
    return (1/fitness)

    # Convert gene_bounds to a list
gene_space = gene_space.tolist()
initial_mutation_percent = 1 #0.0001
final_mutation_percent = 5 #0.05
mutation_percent_genes = [initial_mutation_percent, final_mutation_percent]
keep_parents = 5
num_generations = 5
num_parents_mating = 5
sol_per_pop = 5

    # Create an instance of the pygad.GA class
ga_instance = pygad.GA(num_generations=num_generations,
                        num_parents_mating=num_parents_mating,
                        fitness_func=fitness_func,
                        sol_per_pop=sol_per_pop,
                        num_genes=num_constants,
                        gene_type=float,
                        gene_space=gene_space,
                        mutation_type="adaptive",
                        keep_elitism=1,
                        mutation_percent_genes=mutation_percent_genes,
                        crossover_type="uniform",
                        parent_selection_type="rank",
                        stop_criteria=["reach_10000", "saturate_15"])


ga_instance.run()# Run the genetic algorithm
        

    # Get the best solution and its fitness
solution, solution_fitness, solution_idx = ga_instance.best_solution()
print(solution)
print("Fitness value of the best solution = {solution_fitness}".format(solution_fitness=solution_fitness))

with open("constants.h", "w") as file:  #to save/write the best solution into constants.h file
    file.write("#include <stdio.h>\n")
    file.write("#include <stdlib.h>\n")
    file.write("#include <math.h>\n")
    file.write("#include <string.h>\n")

    #file.write("#define THRESHOLD 3\n")
    file.write("#define STAR_MIN_PIXEL 3\n")
    file.write("#define STAR_MAX_PIXEL 150\n")
    file.write("#define MAX_STARS 100\n")
    file.write("#define SKIP_PIXELS 2\n")
    file.write("#define LENGTH 1216\n")
    file.write("#define BREADTH 916\n")     
    file.write("#define PIXEL_WIDTH 0.00000155\n")
    file.write("#define NUM_MAX_STARS 13\n")
    file.write("//SM constants\n")
    file.write("#define FOCAL_LENGTH 0.0175\n")
    file.write("#define EPSILON 2.2e-15\n")
#  file.write("#define EPSILON {}\n".format(solution[0]))
    file.write("#define DELTA {}\n".format(solution[0]))
    file.write("#define ANG_DIST_TOLERANCE 1.2\n")
    file.write("#define N_GC 8876\n")
    file.write("#define N_KVEC_PAIRS 224792\n")
    file.write("#define Y_MAX 0.9999999999926209\n")
    file.write("#define Y_MIN 0.9900261208247870\n")
    file.write("#define TOL 0.5\n")
    file.write("#define P1 35\n")
    file.write("#define P2 80\n")
    file.write("#define EPSILON_SEQ_ERROR 0.005\n") 
    file.write("#define EPSILON_EST 0.001 \n")


