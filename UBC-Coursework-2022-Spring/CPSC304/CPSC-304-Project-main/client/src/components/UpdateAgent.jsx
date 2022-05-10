import React, {useContext, useEffect, useState} from "react";
import {useParams} from "react-router-dom";
import api from "../apis/api";
import {useNavigate} from "react-router-dom";

const UpdateAgent = () => {
    const {id} = useParams();
    let navigate = useNavigate();
    const [agentID, setAgentID] = useState("");
    const [name, setName] = useState("");
    const [salary, setSalary] = useState("");
    const [email, setEmail] = useState("");
    const [phoneNum, setPhoneNum] = useState("");

    useEffect(async () => {
        try {
            const response = await api.get(`/agents/${id}`);
            setAgentID(response.data.data.agent.agentid)
            setName(response.data.data.agent.aname)
            setSalary(response.data.data.agent.salary)
            setEmail(response.data.data.agent.email)
            setPhoneNum(response.data.data.agent.phonenum)
            console.log(response);
            console.log(email);
        } catch (err) {
            console.log(err)
        }
    }, [])

    const handleSubmit = async (e) => {
        try {
            e.preventDefault();
            await api.put(`agents/${id}`, {
                agentID,
                name,
                salary,
                email,
                phoneNum
            });
            navigate(`/`)
        } catch (err) {
            console.log(err);
        }
    }

    return (
        <div>
            <form action="">
                <div className="form-group">
                    <label htmlFor="agentid">Agent ID</label>
                    <input
                        value ={agentID}
                        onChange={e => setAgentID(e.target.value)}
                        id="agentid"
                        className="form-control"
                        type="number"
                        readOnly/>
                </div>
                <div className="form-group">
                    <label htmlFor="name">Name</label>
                    <input
                        value ={name}
                        onChange={e => setName(e.target.value)}
                        id="name"
                        className="form-control"
                        type="text" />
                </div>
                <div className="form-group">
                    <label htmlFor="salary">Salary</label>
                    <input
                        value ={salary}
                        onChange={e => setSalary(e.target.value)}
                        id="salary"
                        className="form-control"
                        type="number" />
                </div>
                <div className="form-group">
                    <label htmlFor="email">Email</label>
                    <input
                        value ={email}
                        onChange={e => setEmail(e.target.value)}
                        id="email"
                        className="form-control"
                        type="text" />
                </div>
                <div className="form-group">
                    <label htmlFor="phonenum">Phone Number</label>
                    <input
                        value ={phoneNum}
                        onChange={e => setPhoneNum(e.target.value)}
                        id="phonenum"
                        className="form-control"
                        type="text"
                        maxLength="10"/>
                </div>
                <button onClick={handleSubmit} className={"btn btn-primary"}>Submit</button>
            </form>
        </div>
    )
}

export default UpdateAgent;