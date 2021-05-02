#include "Actor.h"

//FIXME glfw -> sfml

Actor::Actor() : Location({0, 0}), Rotation({0, 0}), Scale({0, 0}) {
    Mesh = nullptr;
}

Actor::~Actor() {
    delete Mesh;
    delete Mat;
}

void Actor::InitMesh(const char *filename) {
    Mesh = new StaticMesh;

    Mesh->ReadFile(filename);
    Mesh->Init();
}

void Actor::InitMesh(StaticMesh *Other) {
    Mesh = Other;
}


void Actor::BeginPlay() {
}

void Actor::Tick(float DeltaSeconds) {
    Draw();
}

void Actor::InitMaterialShader(const char *filename) {
    Mat = new Material;

    Mat->InitShaders(filename);
}

void Actor::Draw() {
//    Mat->SetProgram();
//    glPushMatrix();
//    {
//        glTranslatef(Location.X, Location.Y, 0);
//
//        glScalef(Scale.X, Scale.Y, 1);
//        glRotatef(Rotation.X, 1, 0, 0);
//        glRotatef(Rotation.Y, 0, 1, 0);
//
//        Mesh->Draw();
//    }
//    glPopMatrix();
//    Mat->ResetProgram();
}

void Actor::MakeComplexCollision() {
    Collider = std::vector<Collision *>(0);

    for (auto &face : Mesh->faces) {
        Vec2D v1, v2, v3;
        v1.X = Mesh->vertices[face.v1].X;
        v1.Y = Mesh->vertices[face.v1].Y;


        v2.X = Mesh->vertices[face.v2].X;
        v2.Y = Mesh->vertices[face.v2].Y;

        v3.X = Mesh->vertices[face.v3].X;
        v3.Y = Mesh->vertices[face.v3].Y;

        Collider.push_back(new CollisionTriangle(v1, v2, v3, this));
    }

}