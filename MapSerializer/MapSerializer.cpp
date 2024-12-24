//
// Created by Le Hoang An on 24/12/24.
//

#include "MapSerializer.hpp"
void MapSerializer::serialize(std::string inputFile, std::string outputFile) {
    std::ifstream fin;
    fin.open(inputFile);
    if (!fin.is_open()) {
        std::cerr << "Cannot open file " << inputFile << std::endl;
        return;
    }
    std::fstream fout;
    fout.open(outputFile, std::ios::binary | std::ios::out | std::ios::trunc);
    int CharacterSpawnX, CharacterSpawnY;
    fin >> CharacterSpawnX >> CharacterSpawnY;
//    std::cout << CharacterSpawnX << " " << CharacterSpawnY << std::endl;
    fout.write((char*)&CharacterSpawnX, sizeof(CharacterSpawnX));
    fout.write((char*)&CharacterSpawnY, sizeof(CharacterSpawnY));
    int NumberOfEnemies;
    fin >> NumberOfEnemies;
//    std::cout << "Number of Enemies: " << NumberOfEnemies << std::endl;
    fout.write((char*)&NumberOfEnemies, sizeof(NumberOfEnemies));
    for (int i = 0; i < NumberOfEnemies; i++) {
        int EnemyType;
        fin >> EnemyType;
        fout.write((char*)&EnemyType, sizeof(EnemyType));
        int EnemyX, EnemyY;
        fin >> EnemyX >> EnemyY;
//        std::cout << EnemyX << " " << EnemyY << " ";
        fout.write((char*)&EnemyX, sizeof(EnemyX));
        fout.write((char*)&EnemyY, sizeof(EnemyY));
        int EnemyRangeX1, EnemyRangeX2;
        fin >> EnemyRangeX1 >> EnemyRangeX2;
        fout.write((char*)&EnemyRangeX1, sizeof(EnemyRangeX1));
        fout.write((char*)&EnemyRangeX2, sizeof(EnemyRangeX2));
    }
    int NumberOfItems;
    fin >> NumberOfItems;
    std::cout << "Number of Items: " << NumberOfItems << std::endl;
    fout.write((char*)&NumberOfItems, sizeof(NumberOfItems));
    for (int i = 0; i < NumberOfItems; i++) {
        int ItemX, ItemY;
        fin >> ItemX >> ItemY;
        std::cout << ItemX << " " << ItemY << " ";
        fout.write((char*)&ItemX, sizeof(ItemX));
        fout.write((char*)&ItemY, sizeof(ItemY));
    }
    int NumberOfStaticEnvironment;
    fin >> NumberOfStaticEnvironment;
//    std::cout << "Number of Static Environment: " << NumberOfStaticEnvironment << std::endl;
    fout.write((char*)&NumberOfStaticEnvironment, sizeof(NumberOfStaticEnvironment));
    for (int i = 0; i < NumberOfStaticEnvironment; i++) {
        int StaticEnvironmentType;
        fin >> StaticEnvironmentType;
        fout.write((char*)&StaticEnvironmentType, sizeof(StaticEnvironmentType));
        int StaticEnvironmentX, StaticEnvironmentY;
        fin >> StaticEnvironmentX >> StaticEnvironmentY;
//        std::cout << StaticEnvironmentX << " " << StaticEnvironmentY << std::endl;
        fout.write((char*)&StaticEnvironmentX, sizeof(StaticEnvironmentX));
        fout.write((char*)&StaticEnvironmentY, sizeof(StaticEnvironmentY));
    }
    int NumberOfAnimatedEnvironment;
    fin >> NumberOfAnimatedEnvironment;
    fout.write((char*)&NumberOfAnimatedEnvironment, sizeof(NumberOfAnimatedEnvironment));
    for (int i = 0; i < NumberOfAnimatedEnvironment; i++) {
        int AnimatedEnvironmentType;
        fin >> AnimatedEnvironmentType;
        fout.write((char*)&AnimatedEnvironmentType, sizeof(AnimatedEnvironmentType));
        int AnimatedEnvironmentX, AnimatedEnvironmentY;
        fin >> AnimatedEnvironmentX >> AnimatedEnvironmentY;
        fout.write((char*)&AnimatedEnvironmentX, sizeof(AnimatedEnvironmentX));
        fout.write((char*)&AnimatedEnvironmentY, sizeof(AnimatedEnvironmentY));
        int ItemType;
        fin >> ItemType;
        fout.write((char*)&ItemType, sizeof(ItemType));
    }
    int NumberOfDrawables;
    fin >> NumberOfDrawables;
    fout.write((char*)&NumberOfDrawables, sizeof(NumberOfDrawables));
    for (int i = 0; i < NumberOfDrawables; i++) {
        int DrawableType;
        fin >> DrawableType;
        fout.write((char*)&DrawableType, sizeof(DrawableType));
        int DrawableX, DrawableY;
        fin >> DrawableX >> DrawableY;
        fout.write((char*)&DrawableX, sizeof(DrawableX));
        fout.write((char*)&DrawableY, sizeof(DrawableY));
    }
    int NumberOfHoles;
    fin >> NumberOfHoles;
    fout.write((char*)&NumberOfHoles, sizeof(NumberOfHoles));
    for (int i = 0; i < NumberOfHoles; i++) {
        int HoleX, HoleY;
        fin >> HoleX >> HoleY;
        fout.write((char*)&HoleX, sizeof(HoleX));
        fout.write((char*)&HoleY, sizeof(HoleY));
    }
    int NumberOfLifts;
    fin >> NumberOfLifts;
    fout.write((char*)&NumberOfLifts, sizeof(NumberOfLifts));
    for (int i = 0; i < NumberOfLifts; i++) {
        int LiftX, LiftY;
        fin >> LiftX >> LiftY;
        fout.write((char*)&LiftX, sizeof(LiftX));
        fout.write((char*)&LiftY, sizeof(LiftY));
    }
    int NumberOfEndPipe;
    fin >> NumberOfEndPipe;
    fout.write((char*)&NumberOfEndPipe, sizeof(NumberOfEndPipe));
    for (int i = 0; i < NumberOfEndPipe; i++) {
        int EndPipeType;
        fin >> EndPipeType;
        fout.write((char*)&EndPipeType, sizeof(EndPipeType));
        int EndPipeX, EndPipeY;
        fin >> EndPipeX >> EndPipeY;
        fout.write((char*)&EndPipeX, sizeof(EndPipeX));
        fout.write((char*)&EndPipeY, sizeof(EndPipeY));
    }
    int TypeOfLevel;
    fin >> TypeOfLevel;
    fout.write((char*)&TypeOfLevel, sizeof(TypeOfLevel));
    int EndFlags;
    fin >> EndFlags;
    fout.write((char*)&EndFlags, sizeof(EndFlags));
    if (EndFlags == 1) {
        int EndX;
        fin >> EndX;
        fout.write((char*)&EndX, sizeof(EndX));
    }
    else{

    }
    fin.close();
    fout.close();
}
void MapSerializer::deserialize(std::string inputFile, std::string outputFile) {
    std::cout << "Deserializing..." << std::endl;
    std::fstream fin;
    fin.open(inputFile, std::ios::binary | std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Cannot open file " << inputFile << std::endl;
        return;
    }
    std::ofstream fout;
    fout.open(outputFile);
    int CharacterSpawnX, CharacterSpawnY;
    fin.read((char*)&CharacterSpawnX, sizeof(CharacterSpawnX));
    fin.read((char*)&CharacterSpawnY, sizeof(CharacterSpawnY));
    fout << CharacterSpawnX << " " << CharacterSpawnY << std::endl;
    int NumberOfEnemies;
//    std::cout << "Number of Enemies: " << NumberOfEnemies << std::endl;
    fin.read((char*)&NumberOfEnemies, sizeof(NumberOfEnemies));
    fout << NumberOfEnemies << std::endl;

    for (int i = 0; i < NumberOfEnemies; i++) {
        int EnemyType;
        fin.read((char*)&EnemyType, sizeof(EnemyType));
        fout << EnemyType << " ";
        int EnemyX, EnemyY;
        fin.read((char*)&EnemyX, sizeof(EnemyX));
        fin.read((char*)&EnemyY, sizeof(EnemyY));
        fout << EnemyX << " " << EnemyY << " ";
        int EnemyRangeX1, EnemyRangeX2;
        fin.read((char*)&EnemyRangeX1, sizeof(EnemyRangeX1));
        fin.read((char*)&EnemyRangeX2, sizeof(EnemyRangeX2));
        fout << EnemyRangeX1 << " " << EnemyRangeX2 << std::endl;
    }
    int NumberOfItems;
    fin.read((char*)&NumberOfItems, sizeof(NumberOfItems));
    fout << NumberOfItems << std::endl;
    std::cout << "Number of Items: " << NumberOfItems << std::endl;
    for (int i = 0; i < NumberOfItems; i++) {
        int ItemX, ItemY;
        fin.read((char*)&ItemX, sizeof(ItemX));
        fin.read((char*)&ItemY, sizeof(ItemY));
        fout << ItemX << " " << ItemY << std::endl;
        std::cout << ItemX << " " << ItemY << " ";
    }
    std::cout << std::endl;
    int NumberOfStaticEnvironment;
//    std::cout << "Number of Static Environment: " << NumberOfStaticEnvironment << std::endl;
    fin.read((char*)&NumberOfStaticEnvironment, sizeof(NumberOfStaticEnvironment));
    fout << NumberOfStaticEnvironment << std::endl;
    for (int i = 0; i < NumberOfStaticEnvironment; i++) {
        int StaticEnvironmentType;
        fin.read((char*)&StaticEnvironmentType, sizeof(StaticEnvironmentType));
        fout << StaticEnvironmentType << " ";
        int StaticEnvironmentX, StaticEnvironmentY;
        fin.read((char*)&StaticEnvironmentX, sizeof(StaticEnvironmentX));
        fin.read((char*)&StaticEnvironmentY, sizeof(StaticEnvironmentY));
//        std::cout << StaticEnvironmentX << " " << StaticEnvironmentY << std::endl;
        fout << StaticEnvironmentX << " " << StaticEnvironmentY << std::endl;
    }
    int NumberOfAnimatedEnvironment;
    fin.read((char*)&NumberOfAnimatedEnvironment, sizeof(NumberOfAnimatedEnvironment));
    fout << NumberOfAnimatedEnvironment << std::endl;
    for (int i = 0; i < NumberOfAnimatedEnvironment; i++) {
        int AnimatedEnvironmentType;
        fin.read((char*)&AnimatedEnvironmentType, sizeof(AnimatedEnvironmentType));
        fout << AnimatedEnvironmentType << " ";
        int AnimatedEnvironmentX, AnimatedEnvironmentY;
        fin.read((char*)&AnimatedEnvironmentX, sizeof(AnimatedEnvironmentX));
        fin.read((char*)&AnimatedEnvironmentY, sizeof(AnimatedEnvironmentY));
        fout << AnimatedEnvironmentX << " " << AnimatedEnvironmentY << " ";
        int ItemType;
        fin.read((char*)&ItemType, sizeof(ItemType));
        fout << ItemType << std::endl;
    }
    int NumberOfDrawables;
    fin.read((char*)&NumberOfDrawables, sizeof(NumberOfDrawables));
    fout << NumberOfDrawables << std::endl;
    for (int i = 0; i < NumberOfDrawables; i++) {
        int DrawableType;
        fin.read((char*)&DrawableType, sizeof(DrawableType));
        fout << DrawableType << " ";
        int DrawableX, DrawableY;
        fin.read((char*)&DrawableX, sizeof(DrawableX));
        fin.read((char*)&DrawableY, sizeof(DrawableY));
        fout << DrawableX << " " << DrawableY << std::endl;
    }
    int NumberOfHoles;
    fin.read((char*)&NumberOfHoles, sizeof(NumberOfHoles));
    fout << NumberOfHoles << std::endl;
    for (int i = 0; i < NumberOfHoles; i++) {
        int HoleX, HoleY;
        fin.read((char*)&HoleX, sizeof(HoleX));
        fin.read((char*)&HoleY, sizeof(HoleY));
        fout << HoleX << " " << HoleY << std::endl;
    }
    int NumberOfLifts;
    fin.read((char*)&NumberOfLifts, sizeof(NumberOfLifts));
    fout << NumberOfLifts << std::endl;
    for (int i = 0; i < NumberOfLifts; i++) {
        int LiftX, LiftY;
        fin.read((char*)&LiftX, sizeof(LiftX));
        fin.read((char*)&LiftY, sizeof(LiftY));
        fout << LiftX << " " << LiftY << std::endl;
    }
    int NumberOfEndPipe;
    fin.read((char*)&NumberOfEndPipe, sizeof(NumberOfEndPipe));
    fout << NumberOfEndPipe << std::endl;
    for (int i = 0; i < NumberOfEndPipe; i++) {
        int EndPipeType;
        fin.read((char*)&EndPipeType, sizeof(EndPipeType));
        fout << EndPipeType << " ";
        int EndPipeX, EndPipeY;
        fin.read((char*)&EndPipeX, sizeof(EndPipeX));
        fin.read((char*)&EndPipeY, sizeof(EndPipeY));
        fout << EndPipeX << " " << EndPipeY << std::endl;
    }
    int TypeOfLevel;
    fin.read((char*)&TypeOfLevel, sizeof(TypeOfLevel));
    fout << TypeOfLevel << std::endl;
    std::cout << "Type of Level: " << TypeOfLevel << std::endl;
    int EndFlags;
    fin.read((char*)&EndFlags, sizeof(EndFlags));
    fout << EndFlags << std::endl;
    if (EndFlags == 1) {
        std::cout << "End Flags: " << EndFlags << std::endl;
        int EndX;
        fin.read((char*)&EndX, sizeof(EndX));
        fout << EndX << std::endl;
        std::cout << "End X: " << EndX << std::endl;
    }
    else{

    }
    fin.close();
    fout.close();
}