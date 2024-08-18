# UBC Formula E Heartbeat Monitor Challenge ❤️⚡

> [!IMPORTANT]  
> Your first step should be to create a repo using this template repo. Do this by clicking "use this template" on the top right of the page. Please create a **PRIVATE** repo to not leak your submission.

Hey 👋! This repo contains a task given to one of our newcomer software engineers last year

At Formula E, we work with five programmable boards. These boards make up a network along which information from sensors, controls, and telemetry is broadcasted.

Some boards rely on other boards to operate properly.

For example, our _**Vehicle Controller**_ takes in temperature information from the _**Rear Sensor Module**_, accelerator pedal information from the  _**Front Sensor Module**_, and state information from the _**Battery Management System**_ to make decisions.

```
+------------+                       +--------------+
| Vehicle    |    Temperature Data   | Rear Sensor  |
| Controller | <-------------------- | Module       |
|            |                       +--------------+
|            |
|            |                       +--------------------+
|            |         State         | Battery Management |
|            | <-------------------- | System             |
|            |                       +--------------------+
|            |
|            |                       +--------------+
|            |   Accel. Pedal Data   | Front Sensor |
|            | <-------------------- | Module       |
+------------+                       +--------------+
```

Because the Rear Sensor Module, Battery Management System, and Front Sensor Module data is critical to _**operating the car safely**_, if any Board _**fails**_, the Vehicle Controller _**must shutdown as well**_.

```
+------------+                       +--------------+
| Vehicle    |    Temperature Data   | Rear Sensor  |
| Controller | <-------------------- | Module       |
| SHOULD     |                       +--------------+
| SHUTDOWN   |
|            |                       +--------------------+
|            |         State         | Battery Management |
|            | <-------------------- | System             |
|            |                       +--------------------+
|            |
|            |                       +--------------+ ❌
|            |        Bad Data       | Front Sensor | ❌
|            | <---------X---------- | Module FAILS | ❌
+------------+                       +--------------+ ❌
```

We call the system that keeps our board's health in check the _**Heartbeat Monitor**_.

The Rear and Front Sensor Modules, as well as the Battery Management System update a hidden _**heartbeat table**_. The _**heartbeat table**_ has a cell for all boards, and each board updates its respective cell with `true` periodically.

Today we will write a _**Heartbeat Monitor**_ for the next generation UBC Formula E Racecar.

> [!NOTE]  
> *We're interested in seeing how you think about software*, so write down everything, show your thinking, take your time, and don't stress too much!

## Technical Description
You will be implementing the heartbeat monitor for the _**Vehicle Controller**_ described above. We expect your solution to be located at [`problem/solution.c`](./problem/solution.c), where it says `YOUR SOLUTION HERE`.

You are provided an underlying api, found at [`problem/api.h`](./problem/api.h). There is an API reference section below.

The function `task_1Hz` in [`problem/solution.c`](./problem/solution.c) will run every second. Your job is to:
1) Call `shutdown()` if a heartbeat stopped responding in the past second.
2) Call `alert_missing_heartbeat(Board)` with the board that is missing a heartbeat (either `REAR`, `BATTERY`, or `FRONT`).

### Build and Run
To build and run this challenge, just run
```sh
gcc problem/*.c -o main && ./main
```

### API Reference
Can be found at [`problem/api.h`](./problem/api.h).

- `Board`
    - An enum, either `FRONT`, `BATTERY`, or `REAR`, referring to one of the three boards.

- `bool heartbeats_get(Board board)`
    - Reads the status of the heartbeat of a given board from the _**heartbeat table**_

- `void heartbeats_set(Board board, bool status)`
    - Writes a status to the local _**heartbeat table**_.
    > [!NOTE]  
    > Calling `heartbeats_set` updates the _**Vehicle Controller's heartbeat table**_. Note that the Front Sensor Module, Rear Sensor Module, and Battery Management System may write to that table at any time.

- `void alert_missing_heartbeat(Board board)`
    - Alerts that a heartbeat from a given board is missing.

- `void shutdown()`
    - Shuts down the car.

# Submitting your Solution
Once you are happy with your solution, we ask that you do the following two steps to submit.
1) Push to your repo.
2) Invite [Liam Ilan](https://github.com/liam-ilan) as a collaborator (see [github docs](https://docs.github.com/en/account-and-profile/setting-up-and-managing-your-personal-account-on-github/managing-access-to-your-personal-repositories/inviting-collaborators-to-a-personal-repository)).
3) Submit a link to your repo on the application form.

Congrats on making it through this challenge - we'll contact you soon if you are selected for an interview!