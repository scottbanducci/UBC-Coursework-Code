import React, {useContext, useState} from "react";
import api from "../apis/api"
import {AgentsContext} from "../context/AgentsContext";
import {useParams} from "react-router-dom";

const AddTraining = () => {
    const {id} = useParams()
    const {addTraining} = useContext(AgentsContext);
    const [modulenum, setModulenum] = useState(1);
    const [completionDate, setCompletionDate] = useState("");

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await api.post("/agents/trainings", {
                agentid: id,
                modulenum: modulenum,
                completion_date: completionDate
            })
            console.log(response.data.data.training_added);
            addTraining(response.data.data.training_added);
        } catch (err) {
            console.log(err);
        }
    }

    return (
        <div className="card">
            <div className="card-header"> Add a completed training module </div>
            <div className="card-body">
                <form action="">
                    <div className="form-row">
                        <div className="col">
                            <label htmlFor="ModuleNumber">Module Number</label>
                            <input
                                value={modulenum}
                                onChange={e => setModulenum(e.target.value)}
                                type="text"
                                className="form-control"
                                placeholder="Module Number"/>
                        </div>
                        <div className="col">
                            <label htmlFor="CompletionDate">Completion Date</label>
                            <input value={completionDate}
                                   onChange={e => setCompletionDate(e.target.value)}
                                   type="date"
                                   className="form-control"
                                   placeholder="Completion Date"/>
                        </div>
                        <button onClick={handleSubmit} type="submit" className="btn btn-primary">Add</button>
                    </div>
                </form>
            </div>
        </div>
    )
}

export default AddTraining