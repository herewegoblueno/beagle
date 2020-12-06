#include "MutationFactory.h"
#include <stdexcept>
#include <iostream>

std::minstd_rand RNG(std::time(0) + 100);



//For determining mutation chances
std::uniform_int_distribution<> mutationDist(1, 100);

//For determining offset amounts
std::uniform_real_distribution<> offsetDist(-2.f, 2.f);

//Mutation Strategy: Traverse though the tree and mutate things as you go
//As you do this, though, you might encounter nodes that are new to the tree due to
//the mutations you just did on the parents
//This is why you do generation checks.
void mutate(GenotypeNode *current, GenotypeNode *parent, int maxGenToMutate){
    if (current->generation > maxGenToMutate) return; //Skipped

//    //Mutate the current node (if it's not the parent node)
//    if (parent != nullptr){
//        if (mutationDist(RNG) < 10){
//            //10% chance for mutation
//            current = replaceWithRandomTree(current, parent, maxGenToMutate);
//        }
//    }

    if (current->containsClassification(LEAF)){
        if (mutationDist(RNG) < 10){
            //10% chance for offset mutation
            addLeafOffset(current, maxGenToMutate);
        }
    }


//    if (parent != nullptr){
//        if (!current->containsClassification(LEAF)){
//            if (mutationDist(RNG) < 10){
//                //10% chance for mutation
//                current = changeOperator(current, parent, maxGenToMutate);
//            }
//        }
//    }

    //Mutate the children
    for (int i = 0; i < current->numberOfChildrenNeeded; i ++){
       mutate(current->children[i].get(), current, maxGenToMutate);
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

//"For example (abs X) might become (cos X). If this mutation occurs,
//the arguments of the function are also adjusted if necessary to the correct number and types."
//(https://www.karlsims.com/papers/siggraph91.html)
GenotypeNode *changeOperator(GenotypeNode *current, GenotypeNode *parent, int currentGeneration){
    std::unique_ptr<GenotypeNode> newTree = NodeDispenser::getOperationNode();

    SEManager.setNodeGeneration(newTree.get(), currentGeneration + 1);

    int availableChildren = current->numberOfChildrenNeeded;
    //Tranfer all children from old parent to new parent
    int i;
    for (i = 0; i < availableChildren; i ++){
        if (i == newTree->numberOfChildrenNeeded) break; //The old parent gave us everything we need
        newTree->children.push_back(std::move(current->children[i]));
    }

    //If we need more children (so the old parent didn't have enough to give us...)
    //We'll recycle i
    for (; i < newTree->numberOfChildrenNeeded; i++){
        newTree->children.push_back(SEManager.generateTree(50));
        //These new children will need new generations
        SEManager.setTreeGeneration(newTree->children.back().get(), currentGeneration + 1);
    }

    //Let's find the index in the parent's children list that points to the to-be-replaced node
    for (int j = 0; j < parent->numberOfChildrenNeeded; j ++){
        if (parent->children[j].get() == current){
            parent->children[j] = std::move(newTree);
            return parent->children[j].get();
        }
    }

    return nullptr;
}


//This could have been written better but meh it gets the job done without adding
//more member functions to the nodes (or macros)
void addLeafOffset(GenotypeNode *node, int currentGeneration){
    if (XPositionNode * p = dynamic_cast<XPositionNode*>(node) ) {
       p->offsetX = offsetDist(RNG);
       p->offsetY = offsetDist(RNG);
       p->offsetZ = offsetDist(RNG);
    }
    else if (YPositionNode *p = dynamic_cast<YPositionNode*>(node) ) {
        p->offsetX = offsetDist(RNG);
        p->offsetY = offsetDist(RNG);
        p->offsetZ = offsetDist(RNG);
    }
    else if (ZPositionNode *p = dynamic_cast<ZPositionNode*>(node) ) {
        p->offsetX = offsetDist(RNG);
        p->offsetY = offsetDist(RNG);
        p->offsetZ = offsetDist(RNG);
     }
    else if (TimeNode *p = dynamic_cast<TimeNode*>(node) ) {
        p->offsetX = offsetDist(RNG);
        p->offsetY = offsetDist(RNG);
        p->offsetZ = offsetDist(RNG);
     }
    else if (RandomVecNode *p = dynamic_cast<RandomVecNode*>(node) ) {
        p->offsetX = offsetDist(RNG);
        p->offsetY = offsetDist(RNG);
        p->offsetZ = offsetDist(RNG);
     }
    else {
       throw std::invalid_argument("addLeafOffset: Was given a non-leaf node to add offset to!");
    }
    node->generation = currentGeneration + 1;
}

