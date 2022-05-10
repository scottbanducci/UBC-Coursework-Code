import React, {useContext, useEffect} from "react";
import AgentTrainingList from "../components/AgentTrainingList";
import {useParams} from "react-router-dom";
import AddTraining from "../components/AddTraining";

const AgentDetailPage = () => {
    const {id} = useParams()
    return (
        <div>
            <h1>Training Overview Page</h1>
            <AddTraining />
            <AgentTrainingList />
        </div>
    )
}

export default AgentDetailPage