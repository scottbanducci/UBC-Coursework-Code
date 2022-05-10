import React, {useContext, useState} from "react";
import api from "../apis/api"
import {AgentsContext} from "../context/AgentsContext";

const AddAgent = () => {
    const {addAgents} = useContext(AgentsContext);
    const [agentID, setAgentID] = useState("");
    const [name, setName] = useState("");
    const [salary, setSalary] = useState("");
    const [email, setEmail] = useState("");
    const [phoneNum, setPhoneNum] = useState("");

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await api.post("/agents", {
                agentID,
                salary,
                name,
                email,
                phoneNum
            })
            addAgents(response.data.data.agent)
        } catch (err) {
            console.log(err);
        }
    }

    return (
        <div className="card">
            <div className="card-header"> Add an agent </div>
            <div className="card-body">
                <form action="">
                    <div className="form-row">
                        <div className="col">
                            <input
                                value={agentID}
                                onChange={e => setAgentID(e.target.value)}
                                type="number"
                                className="form-control"
                                placeholder="Agent ID"/>
                        </div>
                        <div className="col">
                            <input
                                value={name}
                                onChange={e => setName(e.target.value)}
                                type="text"
                                className="form-control"
                                placeholder="Name"/>
                        </div>
                        <div className="col">
                            <input value={salary}
                                   onChange={e => setSalary(e.target.value)}
                                   type="number"
                                   className="form-control"
                                   placeholder="Salary"/>
                        </div>
                        <div className="col">
                            <input value={email}
                                   onChange={e => setEmail(e.target.value)}
                                   type="text"
                                   className="form-control"
                                   placeholder="Email"/>
                        </div>
                        <div className="col">
                            <input value={phoneNum}
                                   onChange={e => setPhoneNum(e.target.value)}
                                   type="text"
                                   className="form-control"
                                   placeholder="Phone Number"/>
                        </div>
                        <button onClick={handleSubmit} type="submit" className="btn btn-primary">Add</button>
                    </div>
                </form>
            </div>
        </div>
    )
}

export default AddAgent