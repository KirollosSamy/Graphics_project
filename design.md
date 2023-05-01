### المكرمشة:

---

1. high level of abstraction for main modules (objects)
2. how those module might interact (talk to each other ?)
3. the whole flow of the game **(Flow chart**)

   ===================================================
   -*try to study as much as can be for one object, then build the rest of objects
   ===============================================================================

   *-* first approach for one meet the the other for another meet*



MAIN OBJECTS:

* house->some objects within the house
* scary faces
* Granny
* KEY (different sizes)
* 

TODOS:

- Separate objects from house (Texture and  physics of the game )
- Physics Engine


problems:

* granny paths
* collision ?
* download tools and drawer



# We need to see how we can use a physics engine !!?

    



|                        <br />Objects and important questions                        |                                                       Description                                                       | Importance | Logic                                                                                 | Scenario | Assigned to whom |
| :----------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------: | :--------: | ------------------------------------------------------------------------------------- | -------- | :--------------: |
|                         <br />**Granny** ( movement )                         |                          🤔 can be impelemented as Non playable character (NPC) or just static                          |     ✅     | - movement<br />- catch<br />- animations<br />-                                     |          |                  |
|                                  <br />** House**                                  |                              Can we use the house.obj as a whole or make everything alone.                              |     ✅     | - Textures<br />-                                                                    |          |                  |
|                   <br /> The Boy (and the Cage he is trapped in)                   |                                       prisoned in the cage in the hidden room 🤔                                       |            | - Face expressions(change face image)                                                 |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |
|                                  Granny Vs Objects.                                  | Interactions between objects and each other<br />-> How can we make granny come to me if i make a noise in the game () |            | - C**ollision**                                                                |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |
|                                      Game Music                                      |                         How can we set the game music for each<br />situation and for each case                         |            |                                                                                       |          |                  |
|                               <br />Game Scarry Faces                               |                                                     Class scareMe;                                                     |     ✅     |                                                                                       |          |                  |
| <br />How to set timer and track the timer at each frame to check GameOver Condition |                                                   GameOver condition                                                   |            |                                                                                       |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |
|                                     <br />COINS                                     |                            random coins in the house once player step on it he will take it                            |            |                                                                                       |          |                  |
|                                      <br />key                                      |      Random keys hidden in the house one of them is the required one to open the Door<br />and a one for the cage.      |            | - one for house<br />- one for cage                                                   |          |                  |
|                                         door                                         |      exit door (winning condition) -> the door cannot open until i found its key so obvious but also the cage key      |            |                                                                                       |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |
|                      <br />house->some objects within the house                      |                                                                                                                        |            |                                                                                       |          |                  |
|                                        Player                                        |                                                           Me                                                           |     ✅     | - carry<br /><br />- dead ?<br />- camera<br />- movement<br />- hide ?<br />- drop ? |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |
|                                                                                      |                                                                                                                        |            |                                                                                       |          |                  |





| <br />Tasks                                                               | Description | Assigned to whom |
| :------------------------------------------------------------------------ | :---------: | ---------------- |
| <br />**1 - Granny**  (ghost ?) +                                 |      -      | Shredan          |
| 2 - Player+ Light                                                        |      -      | Kiro             |
|                                                                           |      -      |                  |
| 3 - Objects (keys,tools, .....etc) + House (Textures) + Text_instruction |      -      | Nada             |
| 4 - Collision + Music + Scarry Faces                                    |            | Khaled           |
|                                                                           |            |                  |
|                                                                           |            |                  |




| System | Description                                                                                                                                                            | keyWords                                |
| :----: | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------- |
|   S1   | - check for distances between objects<br />if player is in the region of danger he is captured <br />- check if player is too close too object to be able to carry it | - Capture tool<br />- Catched by granny |
|   S2   |                                                                                                                                                                        |                                         |
|        |                                                                                                                                                                        |                                         |
