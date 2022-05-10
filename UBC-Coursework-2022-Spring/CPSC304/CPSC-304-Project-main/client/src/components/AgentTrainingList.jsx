import React, {useContext, useEffect} from "react";
import {AgentsContext} from "../context/AgentsContext";
import {useParams} from "react-router-dom";
import api from "../apis/api";

const AgentTrainingList = () => {
    const {id} = useParams()
    const {selectedAgent, setSelectedAgent, trainings, setTrainings} = useContext(AgentsContext);

    useEffect(async () => {
        try {
            const agentResponse = await api.get(`/agents/${id}`);
            setSelectedAgent(agentResponse.data.data.agent);
        } catch (err) {
            console.log(err);
        }
    }, [])
    useEffect(async () => {
        try {
            const trainingResponse = await api.get(`/agents/${id}/trainings`);
            await setTrainings(trainingResponse.data.data.training_completed)
        } catch (err) {
            console.log(err);
        }
    }, [])

    return (
            <div className="list-group">
                <legend>Trainings completed by {selectedAgent ? selectedAgent.aname : ""}:</legend>
                <table className="table table-hover table-dark">
                    <thead>
                        <tr className="bg-primary">
                            <th scope="col">Module Number</th>
                            <th scope="col">Module Name</th>
                            <th scope="col">Length (Minutes)</th>
                            <th scope="col">Completion Date</th>
                        </tr>
                    </thead>
                    <tbody>
                    {trainings && trainings.map(training => {
                        return (
                            <tr key={training.modulenum}>
                                <td>{training.modulenum}</td>
                                <td>{training.tname}</td>
                                <td>{training.tlength}</td>
                                <td>{new Date(training.completiondate).toDateString()}</td>
                            </tr>
                            )
                    })}
                    </tbody>
                </table>
            </div>
    )
}

export default AgentTrainingList;