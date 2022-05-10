import React, {useState, createContext} from "react";

export const AgentsContext = createContext();

export const AgentsContextProvider = props => {
    const [agents, setAgents] = useState([]);
    const [selectedAgent, setSelectedAgent] = useState(null);
    const [trainings, setTrainings] = useState([]);
    const addAgents = (agent) => {
        setAgents([...agents, agent]);
    }
    const addTraining = (training) => {
        setTrainings([...trainings, training])
    }
    return (
        <AgentsContext.Provider value={{agents, setAgents, addAgents, selectedAgent, setSelectedAgent, trainings, setTrainings, addTraining}}>
            {props.children}
        </AgentsContext.Provider>
    )
}