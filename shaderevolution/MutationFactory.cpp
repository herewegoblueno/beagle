#include "MutationFactory.h"

std::minstd_rand mutationRNG(std::time(0) + 100);
std::uniform_int_distribution<> mutationDist(1, 00);

//Mutation Strategy: Traverse though the tree and mutate things as you go
//As you do this, though, you might encounter nodes that are new to the tree due to
//the mutations you just did on the parents
//This is why you do generation checks.
void mutate(GenotypeNode *current, GenotypeNode *parent, int generationToMutate){
    if (current->generation > generationToMutate) return; //Skipped

    //Mutate the current node (if it's not the parent node)
    if (parent != nullptr){
        if (mutationDist(mutationRNG) < 10){
            //10% chance for mutation
            current = replaceWithRandomTree(current, parent, generationToMutate);
        }
    }

    //Mutate the children
    for (int i = 0; i < current->numberOfChildrenNeeded; i ++){
       mutate(current->children[i].get(), current, generationToMutate);
    }
}

//Returns a pointer to the new tree that replaced current
GenotypeNode *replaceWithRandomTree(GenotypeNode *current, GenotypeNode *parent, int currentGeneration){
    std::unique_ptr<GenotypeNode> newTree = SEManager.generateTree(55);
    SEManager.setTreeGeneration(newTree.get(), currentGeneration + 1);

    //Let's find the index in the parent's children list that points to the to-be-replaced node
    for (int i = 0; i < parent->numberOfChildrenNeeded; i ++){
        if (parent->children[i].get() == current){
            parent->children[i] = std::move(newTree);         
            return parent->children[i].get();
        }
    }

    return nullptr;
}
