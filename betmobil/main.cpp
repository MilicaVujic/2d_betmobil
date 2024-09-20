// Autor: Bogdan Davinic

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>   
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//Biblioteke za pokretanje generatora podataka
#include "TestBed.h"
#define CRES 60 // Circle Resolution = Rezolucija kruga


unsigned int compileShader(GLenum type, const char* source); 
unsigned int createShader(const char* vsSource, const char* fsSource);
static unsigned loadImageToTexture(const char* filePath); //Ucitavanje teksture, izdvojeno u funkciju

int main(void)
{

    //Inicijalizacija objekta tipa Car
    Car car = getCar();
    
    if (!glfwInit()) 
    {
        std::cout<<"GLFW Biblioteka se nije ucitala! :(\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window; 
    unsigned int wWidth = 1200;
    unsigned int wHeight = 800;
    const char wTitle[] = "[Generic Title]";
    window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL); 
    if (window == NULL) 
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate(); 
        return 2; 
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) 
    {
        std::cout << "GLEW nije mogao da se ucita! :'(\n";
        return 3;
    }


    unsigned int unifiedShader = createShader("basic.vert", "basic.frag"); 
    unsigned int lineShader = createShader("line.vert", "line.frag");
    unsigned int pbShader = createShader("pb.vert", "pb.frag");
    unsigned int pbPodeokShader = createShader("pbPodeok.vert", "pbPodeok.frag");
    unsigned int metalShader = createShader("metal.vert", "metal.frag");
    unsigned int engineShader = createShader("engine.vert", "engine.frag");
    unsigned int batteryShader = createShader("battery.vert", "battery.frag");
    unsigned int indikatorBrzineShader = createShader("indikatorBrzine.vert", "indikatorBrzine.frag");
    unsigned int slepiMisShader = createShader("slepiMis.vert", "slepiMis.frag");
    unsigned int imeShader = createShader("ime.vert", "ime.frag");


    float vertices[] = 
    {
       -0.4,-1.0, 0.0,0.0,//1
       -0.4,1.0,  0.0,1.0,//2
       0.4,-1.0,  1.0,0.0,//3
       0.4,1.0,   1.0,1.0//4

    };

    float metal[] =
    {
       -1.0,-1.0, 0.0,0.0,//1
       -1.0,1.0,  0.0,1.0,//2
       1.0,-1.0,  1.0,0.0,//3
       1.0,1.0,   1.0,1.0//4

    };

    float line[] =
    {
        0.0,0.0, 
        -0.20,-0.56 
    };
   
    float progressBar[] =
    {
      0.6,-0.9, 
      0.9,-0.9, 
      0.6,0.8,  
      0.9,0.8

    };

    float progressBarPodeok[] =
    {
      0.65,-0.85,
      0.85,-0.85,
      0.65,-0.845,
      0.85,-0.845

    };

    float engine[] = {
      -0.8,-0.8,    
      -0.7,-0.8,
      -0.8,-0.6,
      -0.7,-0.6


    };

    float battery[] = {
      -0.8,-0.2,
      -0.7,-0.2,
      -0.8,-0.0,
      -0.7,-0.0


    };

    float slepiMis[] = {
     -0.3,0.35,//1
     -0.25,0.3, //2
     -0.15,0.42, //3
     -0.05,0.0, //4
     0.05,0.0,  //5
     0.15,0.42,  //6
     0.25,0.3,  //7
     0.3,0.35 //8
    };

    float ime[] = {
        -1.0,-1.0, 0.0,0.0,
         -0.75,-1.0, 1.0,0.0,
        -1.0,-0.85, 0.0,1.0,
        -0.75,-0.85,  1.0,1.0
    };




    unsigned int stride = (2 + 2) * sizeof(float);
    unsigned int VAO[10];
    glGenVertexArrays(10, VAO); 
    unsigned int VBO[10];
    glGenBuffers(10, VBO); 
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0); 
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float))); 
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(progressBar), progressBar, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
   
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(progressBarPodeok), progressBarPodeok, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(engine), engine, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[6]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(battery), battery, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[9]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ime), ime, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(metal), metal, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO[8]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(slepiMis), slepiMis, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    float circle[CRES * 2 + 4]; // +4 je za x i y koordinate centra kruga, i za x i y od nultog ugla
    float r1 = 0.1; //poluprecnik

    circle[0] = -0.75; //Centar X0
    circle[1] = 0.5; //Centar Y0
    int i;
    for (i = 0; i <= CRES; i++)
    {

        circle[2 + 2 * i] = r1 * cos((3.141592 / 180) * (i * 360 / CRES))/2.2; //Xi
        circle[2 + 2 * i + 1] = r1 * sin((3.141592 / 180) * (i * 360 / CRES)); //Yi
    }

    glBindVertexArray(VAO[7]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    unsigned checkerTexture = loadImageToTexture("res/tablameraca.png"); //Ucitavamo teksturu
    glBindTexture(GL_TEXTURE_2D, checkerTexture); //Podesavamo teksturu
    glGenerateMipmap(GL_TEXTURE_2D); //Generisemo mipmape 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//S = U = X    GL_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// T = V = Y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //GL_NEAREST, GL_LINEAR
    glBindTexture(GL_TEXTURE_2D, 0);
    unsigned uTexLoc = glGetUniformLocation(unifiedShader, "uTex");
    glUniform1i(uTexLoc, 0);


    unsigned metalTexture = loadImageToTexture("res/metal.png"); //Ucitavamo teksturu
    glBindTexture(GL_TEXTURE_2D, metalTexture); //Podesavamo teksturu
    glGenerateMipmap(GL_TEXTURE_2D); //Generisemo mipmape 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//S = U = X    GL_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// T = V = Y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //GL_NEAREST, GL_LINEAR
    glBindTexture(GL_TEXTURE_2D, 0);
    unsigned uTexMetailLoc = glGetUniformLocation(metalShader, "uTex");
    glUniform1i(uTexMetailLoc, 0);

    unsigned imeTexture = loadImageToTexture("res/ime.png"); //Ucitavamo teksturu
    glBindTexture(GL_TEXTURE_2D, imeTexture); //Podesavamo teksturu
    glGenerateMipmap(GL_TEXTURE_2D); //Generisemo mipmape 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//S = U = X    GL_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// T = V = Y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //GL_NEAREST, GL_LINEAR
    glBindTexture(GL_TEXTURE_2D, 0);
    unsigned uTexImeLoc = glGetUniformLocation(imeShader, "uTex");
    glUniform1i(uTexImeLoc, 0);
    
    
    float rgb = 0;
    float r = 0.4;
    unsigned int uULoc = glGetUniformLocation(lineShader, "u");
    unsigned int  uPosLoc = glGetUniformLocation(lineShader, "uPos");
    unsigned int  uPosPodeokLoc = glGetUniformLocation(pbPodeokShader, "uP");
    unsigned int  uEngineULoc = glGetUniformLocation(engineShader, "u");
    unsigned int  uBatteryULoc = glGetUniformLocation(batteryShader, "u");
    unsigned int  uindikaorBrizneULoc = glGetUniformLocation(indikatorBrzineShader, "u");
    unsigned int  uSlepiMisULoc = glGetUniformLocation(slepiMisShader, "uPos");


    float podeoka = 0;
    int prethodni = 0;
    int prethidni1 = 0;

    float x = 0;
    float y = 0;
    startSimulation(&car);

    while (!glfwWindowShouldClose(window)) 
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        {

                car.setCheckEngine(!car.getCheckEngineLight());
        }
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        {

            car.setBatteryLight(!car.getBatteryProblemLight());
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            if (y <= 0.55)
                y += 0.01;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            if (y > -1.0)
                y -= 0.01;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            if (x >= -0.7)
                x -= 0.01;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            if (x <= 0.7)
                x += 0.01;
        }
        
        ;
        glClearColor(0.0,0.0,1.0, 0.5);
        glClear(GL_COLOR_BUFFER_BIT);

        //slepiMis
        int stepen = car.getGear();
        
        //printf("%d", stepen);




        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        }
        else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            glDisable(GL_BLEND);
        }

        if(stepen==2){

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glEnable(GL_PROGRAM_POINT_SIZE);
            glPointSize(8);

            glViewport(0, 520, wWidth, wHeight * 0.35);
            glUseProgram(slepiMisShader);
            glBindVertexArray(VAO[8]);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
            glUniform2f(uSlepiMisULoc, x, y);
           
        }
        else if (stepen == 1) {

            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glEnable(GL_PROGRAM_POINT_SIZE);
            glPointSize(8);

            glViewport(0, 520, wWidth, wHeight * 0.35);
            glUseProgram(slepiMisShader);
            glBindVertexArray(VAO[8]);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
            glUniform2f(uSlepiMisULoc, x, y);

        }
        else if (stepen == 3 || stepen==4 || stepen==5) {

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glViewport(0, 520, wWidth, wHeight * 0.35);
            glUseProgram(slepiMisShader);
            glBindVertexArray(VAO[8]);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
            glUniform2f(uSlepiMisULoc, x, y);
        }
       




        if (stepen != 100) {

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            glViewport(0, 0, wWidth, wHeight * 0.65);
            glUseProgram(metalShader);
            glBindVertexArray(VAO[4]);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, metalTexture);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

            //ime
            glUseProgram(imeShader);
            glBindVertexArray(VAO[9]);
             glActiveTexture(GL_TEXTURE0);
             glBindTexture(GL_TEXTURE_2D, imeTexture);
             glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
             glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);


            //tekstura meraca broja obrtaja

            glUseProgram(unifiedShader);

            glBindVertexArray(VAO[0]);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, checkerTexture);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

            //kazaljka
            rgb = abs(sin(glfwGetTime()));
            glUseProgram(lineShader);
            glBindVertexArray(VAO[1]);
            glLineWidth(10.0);
            glDrawArrays(GL_LINE_STRIP, 0, 2);
            glUniform2f(uPosLoc, 0.5 * cos((3.141592 / 180) * car.getTachometer() * 0.0225) / 3, 0.5 * sin((3.141592 / 180) * car.getTachometer() * 0.0225));
            rgb = abs(sin(glfwGetTime()));

            glUniform1f(uULoc, rgb);

            //pb
            glUseProgram(pbShader);
            glBindVertexArray(VAO[2]);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

            //engine
            glUseProgram(engineShader);
            glBindVertexArray(VAO[5]);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
            if (car.getCheckEngineLight() == true)
                glUniform1f(uEngineULoc, 1);
            else
                glUniform1f(uEngineULoc, 0);


            //battery
            glUseProgram(batteryShader);
            glBindVertexArray(VAO[6]);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
            //printf("%d", car.getBatteryProblemLight());
            if (car.getBatteryProblemLight() == true)
                glUniform1f(uBatteryULoc, 1);
            else
                glUniform1f(uBatteryULoc, 0);

            //indikatorStepenaPrenosa
            glUseProgram(indikatorBrzineShader);
            glBindVertexArray(VAO[7]);
            glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circle) / (2 * sizeof(float)));
            glUniform1f(uindikaorBrizneULoc, abs(sin(glfwGetTime() * (float)stepen)));

            //brina treperenja                  //treperenje


            //pbPodeok
            glUseProgram(pbPodeokShader);
            glBindVertexArray(VAO[3]);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
            glfwSwapBuffers(window);
            float napredak = car.getOdometer();
            napredak = (int)napredak;

            if ((napredak == 2.000000) && (napredak != prethidni1))
            {
                podeoka = 1;
                prethodni = 2.000000;
            }
            if ((napredak == prethodni + 2.000000) && (napredak != prethidni1))
            {
                prethodni = napredak;
                if (podeoka < 10)
                    podeoka += 1;
                else
                    podeoka = 0;
            }
            prethidni1 = napredak;
            glUniform1f(uPosPodeokLoc, podeoka * 0.15);//visina podeoka je 0.15



        }





        glfwPollEvents();
    }

    // Zaustavljanje simulacije
    endSimulation(&car);
    glDeleteBuffers(10, VBO);
    glDeleteVertexArrays(10, VAO);
    glDeleteProgram(unifiedShader);
    glDeleteProgram(lineShader);
    glDeleteProgram(pbShader);
    glDeleteProgram(pbPodeokShader);
    glDeleteProgram(engineShader);
    glDeleteProgram(batteryShader);
    glDeleteProgram(imeShader);
    glDeleteProgram(indikatorBrzineShader);


    glfwTerminate();
    return 0;
}

unsigned int compileShader(GLenum type, const char* source)
{
    //Uzima kod u fajlu na putanji "source", kompajlira ga i vraca sejder tipa "type"
    //Citanje izvornog koda iz fajla
    std::string content = "";
    std::ifstream file(source);
    std::stringstream ss;
    if (file.is_open())
    {
        ss << file.rdbuf();
        file.close();
        std::cout << "Uspjesno procitao fajl sa putanje \"" << source << "\"!" << std::endl;
    }
    else {
        ss << "";
        std::cout << "Greska pri citanju fajla sa putanje \"" << source << "\"!" << std::endl;
    }
     std::string temp = ss.str();
     const char* sourceCode = temp.c_str(); //Izvorni kod sejdera koji citamo iz fajla na putanji "source"

    int shader = glCreateShader(type); //Napravimo prazan sejder odredjenog tipa (vertex ili fragment)
    
    int success; //Da li je kompajliranje bilo uspjesno (1 - da)
    char infoLog[512]; //Poruka o gresci (Objasnjava sta je puklo unutar sejdera)
    glShaderSource(shader, 1, &sourceCode, NULL); //Postavi izvorni kod sejdera
    glCompileShader(shader); //Kompajliraj sejder

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success); //Provjeri da li je sejder uspjesno kompajliran
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog); //Pribavi poruku o gresci
        if (type == GL_VERTEX_SHADER)
            printf("VERTEX");
        else if (type == GL_FRAGMENT_SHADER)
            printf("FRAGMENT");
        printf(" sejder ima gresku! Greska: \n");
        printf(infoLog);
    }
    return shader;
}
unsigned int createShader(const char* vsSource, const char* fsSource)
{
    //Pravi objedinjeni sejder program koji se sastoji od Vertex sejdera ciji je kod na putanji vsSource

    unsigned int program; //Objedinjeni sejder
    unsigned int vertexShader; //Verteks sejder (za prostorne podatke)
    unsigned int fragmentShader; //Fragment sejder (za boje, teksture itd)

    program = glCreateProgram(); //Napravi prazan objedinjeni sejder program

    vertexShader = compileShader(GL_VERTEX_SHADER, vsSource); //Napravi i kompajliraj vertex sejder
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource); //Napravi i kompajliraj fragment sejder

    //Zakaci verteks i fragment sejdere za objedinjeni program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program); //Povezi ih u jedan objedinjeni sejder program
    glValidateProgram(program); //Izvrsi provjeru novopecenog programa

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success); //Slicno kao za sejdere
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        std::cout << "Objedinjeni sejder ima gresku! Greska: \n";
        std::cout << infoLog << std::endl;
    }

    //Posto su kodovi sejdera u objedinjenom sejderu, oni pojedinacni programi nam ne trebaju, pa ih brisemo zarad ustede na memoriji
    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    return program;
}
static unsigned loadImageToTexture(const char* filePath) {
    int TextureWidth;
    int TextureHeight;
    int TextureChannels;
    unsigned char* ImageData = stbi_load(filePath, &TextureWidth, &TextureHeight, &TextureChannels, 0);
    if (ImageData != NULL)
    {
        //Slike se osnovno ucitavaju naopako pa se moraju ispraviti da budu uspravne
        stbi__vertical_flip(ImageData, TextureWidth, TextureHeight, TextureChannels);

        // Provjerava koji je format boja ucitane slike
        GLint InternalFormat = -1;
        switch (TextureChannels) {
        case 1: InternalFormat = GL_RED; break;
        case 3: InternalFormat = GL_RGB; break;
        case 4: InternalFormat = GL_RGBA; break;
        default: InternalFormat = GL_RGB; break;
        }

        unsigned int Texture;
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, TextureWidth, TextureHeight, 0, InternalFormat, GL_UNSIGNED_BYTE, ImageData);
        glBindTexture(GL_TEXTURE_2D, 0);
        // oslobadjanje memorije zauzete sa stbi_load posto vise nije potrebna
        stbi_image_free(ImageData);
        return Texture;
    }
    else
    {
        std::cout << "Textura nije ucitana! Putanja texture: " << filePath << std::endl;
        stbi_image_free(ImageData);
        return 0;
    }
}


