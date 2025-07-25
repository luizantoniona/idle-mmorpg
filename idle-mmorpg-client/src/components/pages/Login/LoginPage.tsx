import "./LoginPage.css";
import { LoginForm, ServerForm } from "../../molecules";

export function LoginPage() {
    return (
        <div className="login-page">
            <ServerForm />
            <LoginForm />
        </div>
    );
}