# CPU-Simulation-of-Events
 an Event Simulator that simulates process events that occur in a typical operating system, using C++
# Setup
Randomly generate all the process events at the beginning of the simulation and store
them in an Event Queue. Then  dequeue events and handle them by making
modifications to any data structures that are created and displaying the output. 
# Events to simulate
ProcessesDidArrive
ProcessDidExit
ProcessDidStartRunning
ProcessDidStopRunning
ProcessDidRequestIO
IODidFinish

# Output 
  Starting simulation
  time: 003 s: Process 1 arrived.
  time: 004 s: Process 1 started running.
  time: 008 s: Process 2 arrived.
  time: 009 s: Process 1 stopped running.
  time: 009 s: Process 2 started running.
  time: 012 s: Process 2 requested IO
  time: 012 s: Process 1 started running.
