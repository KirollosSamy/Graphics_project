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

| <br />Tasks                                            | Description | Assigned to whom |
| :----------------------------------------------------- | :---------: | ---------------- |
| <br />**1 - Granny**  (ghost ?) +              |      -      | Shredan          |
| 2 - Player+ Light                                     |      -      | Kiro             |
|                                                        |      -      |                  |
| 3 - Objects (keys,tools, .....etc) + House (Textures) |      -      | Nada             |
| 4 - Collision + Music + Scarry Faces                 |            | Khaled           |
|                                                        |            |                  |
| Text_instruction                                       |            |                  |

| System | Description                                                                                                                                                            | keyWords                                |
| :----: | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------- |
|   S1   | - check for distances between objects<br />if player is in the region of danger he is captured <br />- check if player is too close too object to be able to carry it | - Capture tool<br />- Catched by granny |
|   S2   |                                                                                                                                                                        |                                         |
|        |                                                                                                                                                                        |                                         |

| Music                                                                                                                                                           | How to use it                                                                                                                                                                                                                                                                                    |
| :-------------------------------------------------------------------------------------------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| -  implemented using mciSendString which is a function in Windows API and is used to send command<br /> strings to control multimedia devices and services. | mciSendString("command  PATH", NULL, 0, NULL);<br />takes variety of commands to control multimedia devices and services in Windows<br /><br />we should call it first with command open and file path to open the audio file<br />then call function again with the needed command and options |

### this commands are :

#### * `open`: Opens a multimedia file or device and assigns it an alias name.

* `close`: Closes a multimedia file or device.
* `play`: Plays a multimedia file or device.
* `stop`: Stops playing a multimedia file or device.
* `pause`: Pauses playback of a multimedia file or device.
* `resume`: Resumes playback of a paused multimedia file or device.
* `seek`: Seeks to a specific location in a multimedia file.
* `set`: Sets various properties of a multimedia device or service, such as volume or playback speed.
* `status`: Retrieves the status of a multimedia device or service, such as the current position of playback.

###### 🔴Scary Faces appears at random times for a certain time (3 to 4 seconds): (Still working on How )

1. Load the image you want to display using an image loading library such as SOIL or DevIL. This will give you a texture ID that you can use to reference the image.
2. Set up an OpenGL quad that will cover the entire screen. You can do this by defining four vertices with texture coordinates that map to the corners of the screen.
3. Bind the texture you loaded in step 1 to the quad using the texture ID.
4. Render the quad to the screen using OpenGL's immediate mode or a vertex buffer object.
5. Wait for the desired amount of time using a timer or sleep function.
6. Clear the front buffer using `glClear()` to remove the quad and any other graphics from the screen.



###### Objects : 

---
