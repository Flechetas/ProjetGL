#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "CuTest.h"
#include "../include/neuralnet/layer.h"
#include "../include/neuralnet/model.h"
#include "../include/neuralnet/ForwardPass.h"

static int equals(float a, float b) {
    float epsilon = 0.0001f; 
    return fabs(a - b) < epsilon;
}

void TestForwardPass(CuTest* tc) {
    // Création d'un modèle simple à 3 couches (2 -> 2 -> 1)
    Layer input = malloc(sizeof(struct layer));
    input->n = 2;
    input->neurons = malloc(sizeof(float) * input->n);
    input->next = NULL;  // Important pour éviter les boucles

    Layer hidden = malloc(sizeof(struct layer));
    hidden->n = 2;
    hidden->neurons = malloc(sizeof(float) * hidden->n);
    hidden->next = NULL;

    Layer output = malloc(sizeof(struct layer));
    output->n = 1;
    output->neurons = malloc(sizeof(float) * output->n);
    output->next = NULL;  // Dernière couche 

    // Connexion des couches
    input->next = hidden;
    hidden->previous = input;
    hidden->next = output;
    output->previous = hidden;

    // Initialisation des poids (matrice de connexion)
    input->w = hidden->n;
    input->weight = malloc(sizeof(float*) * input->n);
    for (int i = 0; i < input->n; i++) {
        input->weight[i] = malloc(sizeof(float) * hidden->n);
    }
    input->weight[0][0] = 0.2;
    input->weight[0][1] = 0.4;
    input->weight[1][0] = 0.3;
    input->weight[1][1] = 0.5;

    hidden->w = output->n;
    hidden->weight = malloc(sizeof(float*) * hidden->n);
    for (int i = 0; i < hidden->n; i++) {
        hidden->weight[i] = malloc(sizeof(float) * output->n);
    }
    hidden->weight[0][0] = 0.6;
    hidden->weight[1][0] = 0.7;

    // Création du modèle
    Model model = malloc(sizeof(struct model));
    model->input = input;
    model->layer_n = 3;

    // Entrée de test
    float input_values[2] = {1.0, 0.5};

    // Exécution de la propagation
    float* result = forwardPass(model, input_values);

    // Calcul des valeurs attendues
    float expected_hidden0 = activationFunction(1.0 * 0.2 + 0.5 * 0.3);
    float expected_hidden1 = activationFunction(1.0 * 0.4 + 0.5 * 0.5);
    float expected_output = activationFunction(expected_hidden0 * 0.6 + expected_hidden1 * 0.7);

    // Assertions
    CuAssertTrue(tc, equals(expected_hidden0, hidden->neurons[0]));
    CuAssertTrue(tc, equals(expected_hidden1, hidden->neurons[1]));
    CuAssertTrue(tc, equals(expected_output, result[0]));

    // Libération mémoire (évite les fuites)
    free(input->neurons);
    
    for (int i = 0; i < input->n; i++) {
        free(input->weight[i]);
    }
    free(input->weight);
    free(input);

    free(hidden->neurons);
    for (int i = 0; i < hidden->n; i++) {
        free(hidden->weight[i]);
    }
    free(hidden->weight);
    free(hidden);

    free(output->neurons);
    free(output);
    free(model);
}

// Test de la propagation 
// Initalisation manuelle des couches (2->3->1), valeurs des neurones et des poids.
void TestManuelForwardPass(CuTest* tc) {

    // Création de la couche d'entrée avec 2 neurones
    Layer input = malloc(sizeof(struct layer));
    input->n = 2;
    input->neurons = malloc(sizeof(float) * 2);
    input->neurons[0] = 1.0;    // initialisation manuelle des neurones
    input->neurons[1] = 0.5;    // " 

    // Création de la couche cachée avec 3 neurones
    Layer hidden = malloc(sizeof(struct layer));
    hidden->n = 3;
    hidden->neurons = malloc(sizeof(float) * 3);

    // Création de la couche de sortie avec 1 neurone
    Layer output = malloc(sizeof(struct layer));
    output->n = 1;
    output->neurons = malloc(sizeof(float) * 1);

    // Connexion des couches : entrée <-> cachée <-> sortie
    input->next = hidden;
    hidden->previous = input;
    hidden->next = output;
    output->previous = hidden;
    
    // ------------------------------------------------------
    // initialisation des poids (manuellement)
    // ------------------------------------------------------

    // poids couche entrée -> caché
    input->w = hidden->n;
    input->weight = malloc(sizeof(float*) * input->n);
    for (int i = 0; i < input->n; i++) {
        input->weight[i] = malloc(sizeof(float) * hidden->n); // matrice n * w (ici 2x3)
    }
    
    input->weight[0][0] = 0.2;
    input->weight[0][1] = 0.3;
    input->weight[0][2] = 0.4;

    input->weight[1][0] = 0.5;
    input->weight[1][1] = 0.6;
    input->weight[1][2] = 0.7;

    // poids couche caché -> sortie
    hidden->w = output->n;
    hidden->weight = malloc(sizeof(float*) * hidden->n);
    for (int i = 0; i < hidden->n; i++) {
        hidden->weight[i] = malloc(sizeof(float) * output->n); // 3x1
    }

    hidden->weight[0][0] = 0.1;
    hidden->weight[1][0] = 0.2;
    hidden->weight[2][0] = 0.3;

    // ------------------------------------------------------
    // Calcul somme + transfert
    // ------------------------------------------------------

    // Pour la couche caché
    for (int j = 0; j < hidden->n; j++) {
        float sum = 0.0;
        for (int i = 0; i < input->n; i++) {
            sum += input->neurons[i] * input->weight[i][j];
        }
        // Application de tanh sur la somme
        hidden->neurons[j] = activationFunction(sum);
    }

    // Pour la couche de sortie
    for (int k = 0; k < output->n; k++) {
        float sum = 0.0;
        for (int j = 0; j < hidden->n; j++) {
            sum += hidden->neurons[j] * hidden->weight[j][k];
        }
        output->neurons[k] = activationFunction(sum);
    }

    // Valeurs attendues --

    // Pour la couche caché :
    // n0 : sum = 1.0*0.2 + 0.5*0.5 = 0.2 + 0.25 = 0.45
    float expected_hidden0 = activationFunction(0.45);
    // n1 : sum = 1.0*0.3 + 0.5*0.6 = 0.3 + 0.3 = 0.6
    float expected_hidden1 = activationFunction(0.6);
    // n2 : sum = 1.0*0.4 + 0.5*0.7 = 0.4 + 0.35 = 0.75
    float expected_hidden2 = activationFunction(0.75);

    // Pour la couche de sortie :
    // sum = expected_hidden0*0.1 + expected_hidden1*0.2 + expected_hidden2*0.3
    float expected_output_sum = expected_hidden0 * 0.1 + expected_hidden1 * 0.2 + expected_hidden2 * 0.3;
    float expected_output = activationFunction(expected_output_sum);


    // --- Comparaison avec les valeurs calculées ---
    CuAssertTrue(tc, equals(expected_hidden0, hidden->neurons[0]));
    CuAssertTrue(tc, equals(expected_hidden1, hidden->neurons[1]));
    CuAssertTrue(tc, equals(expected_hidden2, hidden->neurons[2]));

    CuAssertTrue(tc, equals(expected_output, output->neurons[0]));

    // gestion mémoire
    free(input->neurons);
    for (int i = 0; i < input->n; i++){
       free(input->weight[i]);
    }
    free(input->weight);
    free(input);

    free(hidden->neurons);
    for (int i = 0; i < hidden->n; i++){
       free(hidden->weight[i]);
    }
    free(hidden->weight);
    free(hidden);

    free(output->neurons);
    free(output);
}


CuSuite* CuGetForwardPassSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestManuelForwardPass);
    SUITE_ADD_TEST(suite, TestForwardPass);

    return suite;
}