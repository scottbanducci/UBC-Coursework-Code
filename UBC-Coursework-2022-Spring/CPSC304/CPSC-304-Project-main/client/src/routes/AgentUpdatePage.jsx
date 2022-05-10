import React from "react";
import UpdateAgent from "../components/UpdateAgent";
import {useParams} from "react-router-dom";

const AgentUpdatePage = () => {
    const {id} = useParams()
    return (
        <div>
            <h1 className="text-center">Update Agent {id}</h1>
            <UpdateAgent />
        </div>
    )
}

export default AgentUpdatePage