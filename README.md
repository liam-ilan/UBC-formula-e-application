# UBC FE Challenge - Cardiovehicular Surgery ❤️⚡

> [!IMPORTANT]  
> Your first step should be to create a repo using this template repo. Do this by clicking "use this template" on the top right of the page. Please create a **PRIVATE** repo to not leak your submission.

Hey 👋! This repo contains a task given to one of our newcomer software engineers last year

At Formula E, we work with five programmable boards. These boards make up a network along which information from sensors, controls, and telemetry is broadcast.

Some boards rely on other boards to operate properly.

For example, our _**Vehicle Controller**_ takes in temprature information from the _**Rear Sensor Module**_ and accelerator pedal information from the  _**Front Sensor Module**_ to drive decisions.

```
+------------+                       +--------------+
| Vehicle    |    Temprature Data    | Rear Sensor  |
| Controller | <-------------------- | Module       |
|            |                       +--------------+
|            |
|            |                       +--------------+
|            |   Accel. Pedal Data   | Front Sensor |
|            | <-------------------- | Module       |
+------------+                       +--------------+
```

Because the Rear Sensor Module and Front Sensor Module data is critical to _**operating the car safely**_, if any Sensor Module _**fails**_, the Vehicle Controller _**must shutdown as well**_.


```
+------------+                       +--------------+
| Vehicle    |    Temprature Data    | Rear Sensor  |
| Controller | <-------------------- | Module       |
| SHOULD     |                       +--------------+
| SHUTDOWN   |
|            |                       +--------------+ ❌
|            |        Bad Data       | Front Sensor | ❌
|            | <---------X---------- | Module FAILS | ❌
+------------+                       +--------------+ ❌
```

We call the system that keeps our board's health in check the _**Heartbeat Monitor**_.

Today we will write a _**Heartbeat Monitor**_ for the next generation UBC Formula E Racecar.

> [!NOTE]  
> *We're interested in seeing how you think about software*, so write down everything, show your thinking, take your time, and don't stress too much!

## Technical Description
You will be implementing the hearbeat monitor for the _**Vehicle Controller**_ described above. We expect your solution to be located at [`problem/solution.c`](./problem/solution.c), where it says `YOUR SOLUTION HERE`.

You are provided an underlying api, found at [`problem/api.h`](./problem/api.h)

The function `task_1Hz` in [`problem/solution.c`](./problem/solution.c) will run every second. Your job is to:
1) Call `shutdown()` if a heartbeat stopped responding in the past second.
2) Call `alert_missing_heartbeat(Board)` with the board that is missing a heartbeat (either `REAR` or `FRONT`).

Under the hood, the Rear and Front Sensor Modules update a hidden _**heartbeat table**_. The _**heartbeat table**_ has a cell for both sensor modules, and each module updates its respective cell with `true` periodically.

> [!NOTE]  
> Calling `heartbeats_set` only updates your local _**heartbeat table**_, and does not stop the Front and Rear Sensor Modules from writing to the table.

### Build and Run
To build and run this challenge, just run
```sh
gcc problem/*.c -o main && ./main
```

### API Reference
Can be found at [`problem/api.h`](./problem/api.h).

- `Board`
    - An enum, either `FRONT` or `REAR`, reffering to one of the two sensor modules.

- `bool heartbeats_get(Board board)`
    - Reads the status of the heartbeat of a given board from the _**heartbeat table**_

- `void heartbeats_set(Board board, bool status)`
    - Writes a status to the local _**heartbeat table**_.

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