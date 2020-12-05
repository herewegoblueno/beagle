#ifndef MUTATIONFACTORY_H
#define MUTATIONFACTORY_H

#include "AstNodes.h"
#include <random>
#include "ShaderEvolutionManager.h"
#include "NodeDispenser.h"

void mutate(GenotypeNode *current, GenotypeNode *parent, int generationToMutate);

GenotypeNode *replaceWithRandomTree(GenotypeNode *current, GenotypeNode *parent, int currentGeneration);
void addLeafOffset(GenotypeNode *current, int currentGeneration);
GenotypeNode *changeOperator(GenotypeNode *current, GenotypeNode *parent, int currentGeneration);


#endif // MUTATIONFACTORY_H
