# TJE_Framework - ATOM

## Developers

| Name                | NIA       | Email                                 |
|---------------------|-----------|---------------------------------------|
| Jorge Villarino     | 123456789 | jorge.villarino01@estudiant.upf.edu   |
| Alejandro Vílchez   | 242557    | alejandro.vilchez01@estudiant.upf.edu |

##Changes

- Now you can go to main menú and start a new game. The death by missile now works and send you to the lose screen, instead of blocking.
- New HUD information, now it says when you are correctly dodgin a missile and when not, and the objective that you should bomb is marked in the screen. Also, it has better colors.
- Now you can also click the menu options with the mouse, also the lose and win screens options, and in tutorial you can click to change.
- Some values were changed to offer a better game experience, among others the missile system works a little bit better, the bomb drop position is more accurate, etc.
- Now the plane starts flying in the direction of the island, instead of going back.
- New skybox, more aesthetically coherent with the map.
- Some sound errors have been corrected, some persist.
- New tutorial screen added, to give more information about how to play and win.


## Project Description

Atom is a flight simulator game where the player controls a B-2 bomber plane and must drop atomic bombs over the enemy's island. The goal is to land the bomb in the objective and avoid the enemy radar in order to survive. 

## Blocks of the Game

### Player Entity
- **Developer:** Alejandro Vílchez
- **Description:** Coding of the player's capabilities suchs as the dropping of boms and the movement of the plane, and its camera view. 
- **Developer:** Jorge Villarino
- **Description:** Coding of the player's camera view, the bomb physics and the missile system. 

### World
- **Developer:** Jorge Villarino
- **Description:** Code structure and organization of the World class for the play stage. Implementation of the map.
- **Developer:** Alejandro Vílchez
- **Description:** Implementation of the skybox and the different meshes, including the player entity.

### Stages
- **Developer:** Jorge Villarino
- **Description:** Structure of the stages for the implementation of the game. Designing of the main menu, tutorials and play stage.
- **Developer:** Alejandro Vílchez
- **Description:** Designing of the end stages and the credits.

### Audio
- **Developer:** Jorge Villarino
- **Description:** Implementation of music and sound for the events of the game.

# Clone the repository from GitHub:
   ```sh
   git clone https://github.com/alejandroVilchez/TJE_Framework.git
