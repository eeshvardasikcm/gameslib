# gameslib
gameslib module 
# Firebase Integration
Firebase is emerging as a relevant and useful
way for games to transmit and store their game data online.
Eeshvar Das is developing a Google Cloud platform compute engine virtual machine 
binary for Linux that 
will allow game developers
to use Firebase without any knowledge of how Firebase operates.
## History of gameslib by Eeshvar Das
A private repository preceding gameslib was created in 2021 by Eeshvar Das 
as a way to bring the Shrota language into game development.
just before the equinox of winter entering 2023,
gameslib moves into public view.
Eeshvar Das is now a community contributor in Google's carbon project.
the easiest route to proceed forward with gameslib
is to maintain gameslib
using the same techniques
that Eeshvar Das
is using in his carbon project fork.
## Installing gameslib
Downloading a clone of this repository should work fairly well, 
however upon creating a new android studio project for game activity,
Android Studio is unable to build the project.
I did make some small changes to the build files.
These changes usually don't break a default Android Studio Dolphin Project.
Android Studio Dolphin Games Activity UI allows creating the project 
to target Android 13.
The appearance is that the version of Android should not be problem.
### Issue with CMake in Android Studio (workaround possibly available)
*Workaround:
Vulcan has active code that depends on GameActivity and the ndk.
Look into finding how Vulcan handles this issue*
I am working on solving this issue so I can proceed using Game Activity
as a default feature of Android Studio Dolphin.
I browsed the current commits to the Google games SDK,
and my impression is that Google games SDK is actively 
developing for Android 10 compatibility.
- Downgrading to older versions of ndk and cmake is working for me in Dolphin.
I will update gameslib with the new updates from my private build platform.
development schedule has been clearly outlined in my private repository.
The updates should help to achieve a lower quality C++ build in gameslib for now.
The Android team at Google appears to be reducing ndk dependencies very rapidly.
Newer ndk releases appear to be following new releases of cmake very well.
At this rate, Google will synchronize GamesActivity with cmake and their other libraries efficiently over the next set of releases.
## FAQ
- Q: Where is all the games code?
  - A: previous iterations of gameslib remain as private repositories
until they resurface publicly.
- Q: When will game code be committed to this repository?
  - A: gameslib doesn't contain games code at this time.
The technique of gameslib is to 
allow Firebase game developers 
to have a modern and evolving framework
that is centered around
the evolution of Google's carbon project.
